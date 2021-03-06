import os
import inspect
import pdb
import math
import time
from types import *
from collections import namedtuple

# import wxversion
# wxversion.select("2.8")
import wx
import wx.aui

import instanceEditor
import entityDetailsDialog
import umlEditor
from project import Project, ProjectTreePanel, EVT_PROJECT_LOADED, EVT_PROJECT_NEW
import common
import model

class SAFplusFrame(wx.Frame):
    """
    Frame for the SAFplus UML editor
    """
    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, -1, title, pos=(150, 150), size=(800, 600))
        self.model = None
        self.currentActivePrj = None # indicating that this the current project which is active
       # Create the menubar
        self.menuBar = wx.MenuBar()
        # and a menu 
        self.menu = wx.Menu()
        self.menuModelling = wx.Menu()
        self.menuInstantiation = wx.Menu()
        self.menuWindows = wx.Menu()
        self.menuHelp = wx.Menu()
        # and a toolbar
        self.tb = self.CreateToolBar()
        self.tb.SetToolBitmapSize((24,24))
        # add an item to the menu, using \tKeyName automatically
        # creates an accelerator, the third param is some help text
        # that will show up in the statusbar
        self.menu.Append(wx.ID_EXIT, "E&xit\tAlt-X", "Exit")

        # bind the menu event to an event handler
        self.Bind(wx.EVT_MENU, self.OnTimeToClose, id=wx.ID_EXIT)
        self.Bind(EVT_PROJECT_LOADED, self.OnProjectLoaded)
        self.Bind(EVT_PROJECT_NEW, self.OnProjectLoaded) # Basically, new project is like load project. With new project, at the beginning, data for it was created although it's empty. After that, the newly created project is loaded with its data model

        # and put the menu on the menubar
        self.menuBar.Append(self.menu, "&File")
        self.menuBar.Append(self.menuModelling, "&Modelling")
        self.menuBar.Append(self.menuInstantiation, "&Instantiation")
        self.menuBar.Append(self.menuWindows, "&Windows")
        self.menuBar.Append(self.menuHelp, "&Help")

        self.SetMenuBar(self.menuBar)

        self.sb = self.CreateStatusBar()
        
        self.guiPlaces = common.GuiPlaces(self,self.menuBar, self.tb, self.sb, { "File": self.menu, "Modelling":self.menuModelling, "Instantiation":self.menuInstantiation, "Windows": self.menuWindows, "Help": self.menuHelp }, None)

        # Now create the Panel to put the other controls on.
        panel = self.panel = None # panelFactory(self,menuBar,tb,sb) # wx.Panel(self)
        self.prjSplitter = wx.SplitterWindow(self, style=wx.SP_3D)
        self.project = ProjectTreePanel(self.prjSplitter,self.guiPlaces)
        self.Bind(wx.EVT_TREE_ITEM_ACTIVATED, self.onPrjTreeActivated, self.project.tree) # handle an event when user double-clicks on a project at the tree on the left to switch views to it or to set it active
        self.tab = wx.aui.AuiNotebook(self.prjSplitter)
        self.help = wx.TextCtrl(self.tab, -1, "test", style=wx.TE_MULTILINE)
        self.tab.AddPage(self.help, "Welcome")        
        self.Bind(wx.aui.EVT_AUINOTEBOOK_PAGE_CLOSE, self.onPageClosing, self.tab) # handle tab page close
        self.prjSplitter.SplitVertically(self.project,self.tab,200)
        # And also use a sizer to manage the size of the panel such
        # that it fills the frame
        self.sizer = wx.BoxSizer()
        self.sizer.Add(self.prjSplitter, 1, wx.EXPAND)
        self.SetSizer(self.sizer)

    def cleanupTabs(self):
      """remove all editor window tabs"""
      # while 1:
        #w = self.tab.GetPage(0)
        #if not w: break
      while self.tab.DeletePage(0): pass

    def OnProjectLoaded(self,evt):
      """Called when a project is loaded in the project tree"""
      print "New project loaded"

      # clean up -- if we support multi-projects this won't happen
      #self.cleanupTabs()
      #self.model = {}

      # Now load the new one:
      # prj = self.project.active()
      prj = self.project.latest()      
      self.showProject(prj)

    def showProject(self, prj):
      if not prj: return
      self.currentActivePrj = prj
      self.tab.Unbind(wx.aui.EVT_AUINOTEBOOK_PAGE_CHANGED) # need to unbind to not catch page delete event b/c we only want to catch page selection event
      if not self.model:
        self.cleanupTabs()
        self.model = t = namedtuple('model','model uml instance modelDetails instanceDetails')
        t.model = model.Model()
        prj.setSAFplusModel(t.model)
        modelFile = os.path.join(prj.directory(), prj.model.children()[0].strip())
        t.model.load(modelFile)
        t.uml = umlEditor.Panel(self.tab,self.guiPlaces, t.model)
        self.tab.AddPage(t.uml, self.getCurrentPageText(0))
        t.modelDetails = entityDetailsDialog.Panel(self.tab,self.guiPlaces, t.model,isDetailInstance=False)
        self.tab.AddPage(t.modelDetails, self.getCurrentPageText(1), select=True)
        t.instance = instanceEditor.Panel(self.tab,self.guiPlaces, t.model)
        self.tab.AddPage(t.instance, self.getCurrentPageText(2))
        t.instanceDetails = entityDetailsDialog.Panel(self.tab,self.guiPlaces, t.model,isDetailInstance=True)
        self.tab.AddPage(t.instanceDetails, self.getCurrentPageText(3))
      else:
        print 'OnProjectLoaded: model is not None'
        t = self.model
        prj.setSAFplusModel(t.model)
        modelFile = os.path.join(prj.directory(), prj.model.children()[0].strip())
        t.model.init()
        t.model.load(modelFile)
        t.uml.setModelData(t.model)
        t.uml.deleteTools()
        t.uml.addTools()
        self.setPagesText()
        t.uml.refresh()
        t.instance.setModelData(t.model)
        t.instance.addTools()
        t.instance.refresh()
        t.instanceDetails.setModelData(t.model)
        t.instanceDetails.refresh()
        t.modelDetails.refresh()
      self.tab.Bind(wx.aui.EVT_AUINOTEBOOK_PAGE_CHANGED, self.onPageChanged) # bind to catch page selection event
      self.tab.SetSelection(0) # open uml model view by default
      
    def OnProjectNew(self,evt):
      """Called when a new project is created"""
      print "New project created"

      # clean up -- if we support multi-projects this won't happen
      self.cleanupTabs()
      self.model = {}

      # Now create the new one:
      #prj = self.project.active()
      prj = self.project.latest()
      if not prj: return
      self.model[prj.name] = t = namedtuple('model','model uml instance details')
      # only 1 model file allowed for now
      t.model = model.Model()
      prj.setSAFplusModel(t.model)
      modelFile = os.path.join(prj.directory(), prj.model.children()[0].strip())
      #t.model.loadModuleFromFile(prj.datamodel)
      t.model.load(modelFile)
      t.uml = umlEditor.Panel(self.tab,self.guiPlaces, t.model)
      self.tab.AddPage(t.uml, prj.name + " Modelling")
      t.details = entityDetailsDialog.Panel(self.tab,self.guiPlaces, t.model,isDetailInstance=False)
      self.tab.AddPage(t.details, prj.name + " Model Details")
      t.instance = instanceEditor.Panel(self.tab,self.guiPlaces, t.model)
      self.tab.AddPage(t.instance, prj.name + " Instantiation")
      t.details = entityDetailsDialog.Panel(self.tab,self.guiPlaces, t.model,isDetailInstance=True)
      self.tab.AddPage(t.details, prj.name + " Instance Details")

    def OnTimeToClose(self, evt):
      """Event handler for the button click"""
      print "Quitting..."
      self.Close()
   
    def setPagesText(self):
      self.tab.SetPageText(0, self.getCurrentPageText(0))
      self.tab.SetPageText(1, self.getCurrentPageText(1))
      self.tab.SetPageText(2, self.getCurrentPageText(2))
      self.tab.SetPageText(3, self.getCurrentPageText(3))

    def onPrjTreeActivated(self, evt):
      """ handle an event when user double-clicks on an item at the tree on the left to switch views to it or to set it active """
      pt = evt.GetPoint()
      item, _ = self.project.tree.HitTest(pt)
      if item:       
        print "onPrjTreeActivated [%s]" % self.project.tree.GetItemText(item)
        if self.project.tree.GetItemParent(item) == self.project.root: # check to see if this is the project name
          prjname = os.path.splitext(self.project.tree.GetItemText(item))[0]
          print 'project [%s] is activated' % prjname
          prj = self.project.active()
          print 'project [%s] is selected' % prj.name
          if prj == self.currentActivePrj:
            return
          else:
            self.showProject(prj)
        else: pass #TODO : handling other tree item clicked e.g. c++ source or others

    def onPageChanged(self, evt):
      page = self.tab.GetPageText(evt.GetSelection())
      print 'onPageChangedEvent: page [%s] is selected' % page
      self.enableTools(page)

    def enableTools(self, page):
      t = self.model
      if not t: return      
      if page == self.getCurrentPageText(0):
        # uml modelling is selected, now enable tools belonging to it and disable the others not belonging to it
        if t.uml: 
          t.uml.enableTools(True)
          t.uml.enableMenuItems(True) # set menu items state also
        if t.instance:
          t.instance.enableTools(False)
          t.instance.enableMenuItems(False) # set menu items state also
      elif page == self.getCurrentPageText(2):
        # instantiation is selected, now enable tools belonging to it and disable the others not belonging to it
        if t.uml:
          t.uml.enableTools(False)
          t.uml.enableMenuItems(False)
        if t.instance:
          t.instance.enableTools(True)
          t.instance.enableMenuItems(True)
      else:
        # disable all tools because in these pages, we do not model
        if t.uml:
          t.uml.enableTools(False)
          t.uml.enableMenuItems(False)
        if t.instance:
          t.instance.enableTools(False)
          t.instance.enableMenuItems(False)

    def getCurrentPageText(self, pageIdx):
      if pageIdx==0:
        return self.currentActivePrj.name + " Modelling"
      elif pageIdx==1:
        return self.currentActivePrj.name + " Model Details"
      elif pageIdx==2:
        return self.currentActivePrj.name + " Instantiation"
      elif pageIdx==3:
        return self.currentActivePrj.name + " Instance Details"
      return None

    def onPageClosing(self, evt):
      print 'page closing event launched'
      idx = evt.GetSelection()
      pageText = self.tab.GetPageText(idx)
      print 'page [%s] idx [%d] closing' % (pageText, idx)
      t = self.model
      if pageText == self.getCurrentPageText(0):
        t.uml.deleteMyTools()        
        pageIdx = 0
      elif pageText == self.getCurrentPageText(1):
        pageIdx = 1
      elif pageText == self.getCurrentPageText(2):
        t.instance.deleteMyTools()
        pageIdx = 2
      else:
        pageIdx = 3 
      print 'insert menu item id [%d] text [%s]' % (pageIdx, pageText)
      self.menuWindows.Append(pageIdx, pageText)
      self.menuWindows.Bind(wx.EVT_MENU, self.onWindowsMenu, id=pageIdx)
      #evt.Veto()   
      #self.tab.RemovePage(idx)

    def onWindowsMenu(self, evt):
      print 'onWindowsMenu launched'
      idx = evt.GetId()
      pageText = self.menuWindows.GetLabel(idx)
      print 'menu item [%s] idx [%d] clicked' % (pageText, idx)
      t = self.model
      if pageText == self.getCurrentPageText(0):
        if t.instance:
          t.instance.deleteTools()
        else:
          self.tb.ClearTools()
        page = t.uml = umlEditor.Panel(self.tab,self.guiPlaces, t.model)
        if t.instance:
          t.instance.addTools()
        pageIdx = 0  
      elif pageText == self.getCurrentPageText(1):
        page = t.modelDetails = entityDetailsDialog.Panel(self.tab,self.guiPlaces, t.model,isDetailInstance=False)
        pageIdx = 1 if self.tab.GetPageCount()>1 else 0          
      elif pageText == self.getCurrentPageText(2):
        page = t.instance = instanceEditor.Panel(self.tab,self.guiPlaces, t.model)
        pageIdx = 2 if self.tab.GetPageCount()>1 else 0
      else:
        page = t.instanceDetails = entityDetailsDialog.Panel(self.tab,self.guiPlaces, t.model,isDetailInstance=True)
        pageIdx = 3 if self.tab.GetPageCount()>1 else 0
      print 'insert page id [%d] text [%s]' % (pageIdx, pageText)
      self.tab.InsertPage(pageIdx, page, pageText)
      self.menuWindows.Delete(idx)
      self.tab.SetSelection(pageIdx)

class SAFplusApp(wx.App):
    """ WX Application wrapper for SAFplus IDE"""
    def __init__(self, redirect):
      wx.App.__init__(self, redirect=redirect)

    def OnInit(self):
      self.frame = SAFplusFrame(None, "SAFplus IDE")
      self.SetTopWindow(self.frame)

      print "Print statements go to this stdout window by default."
      self.frame.Show(True)
      return True


def go():
  global app
  common.programDirectory = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe()))) 
  app = SAFplusApp(redirect=False)
  app.MainLoop()

import threading

guithread = None

def start(panelFactory):
  global guithread
  args = None 
  guithread = threading.Thread(group=None, target=go, name="GUI",args = args)
  guithread.start()


if __name__ == "__main__":
  go()


def Test():
  go()
