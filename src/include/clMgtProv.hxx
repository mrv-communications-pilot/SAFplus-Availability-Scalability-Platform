/*
 * Copyright (C) 2002-2012 OpenClovis Solutions Inc.  All Rights Reserved.
 *
 * This file is available  under  a  commercial  license  from  the
 * copyright  holder or the GNU General Public License Version 2.0.
 *
 * The source code for  this program is not published  or otherwise
 * divested of  its trade secrets, irrespective  of  what  has been
 * deposited with the U.S. Copyright office.
 *
 * This program is distributed in the  hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied  warranty  of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * For more  information, see  the file  COPYING provided with this
 * material.
 */

/**
 *  \file
 *  \brief Header file of the MgtProv class which provides APIs to manage "provisioned" objects
 *  \ingroup mgt
 */

/**
 *  \addtogroup mgt
 *  \{
 */
#pragma once
#ifndef CLMGTPROV_HPP_
#define CLMGTPROV_HPP_

#include <typeinfo>
#include <iostream>

extern "C"
{
#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
} /* end extern 'C' */

#include "clMgtObject.hxx"
#include "clMgtDatabase.hxx"
#include "clLogApi.hxx"

namespace SAFplus
{
  /**
   *  MgtProv class provides APIs to manage "provisioned" objects.  Provisioned objects are those that represent configuration that needs to be set by the operator.  This is in contrast to statistics objects which are not set by the operator.
   */
  template<class T>
    class MgtProv : public MgtObject
    {
    protected:
      /* This variable is used to index the value in Transaction object.*/
      ClInt32T mValIndex;

    public:
      /**
       *  Value of the "MgtProv" object
       */
      T value;

    public:
      MgtProv(const char* name);
      virtual ~MgtProv();

      virtual void toString(std::stringstream& xmlString,int depth=SAFplusI::MgtToStringRecursionDepth,SerializationOptions opts=SerializeNoOptions);
      virtual std::string strValue();

      /**
       * \brief   Define basic assignment operator
       */
      MgtProv<T>& operator =(const T& val)
      {
        value = val;
        setDb();
        return *this;
      }
      /**
       * \brief   Define basic access (type cast) operator
       */
      operator T&()
      {
        return value;
      }
      /**
       * \brief   Define basic comparison
       */
      bool operator ==(const T& val)
      {
        return value == val;
      }

      /**
       * \brief   Virtual function to validate object data
       */
      virtual ClBoolT set(const void *pBuffer, ClUint64T buffLen, SAFplus::Transaction& t);
      virtual void xset(const void *pBuffer, ClUint64T buffLen, SAFplus::Transaction& t);

      virtual bool set(const T& value, SAFplus::Transaction& t = SAFplus::NO_TXN);

      /**
       * \brief   Define formal access operation
       */
      T& val()
      {
        return value;
      }

      inline friend std::ostream &operator<<(std::ostream &os, const MgtProv &b)
      {
        return os << (T) b.value;
      }

      inline friend std::istream &operator>>(std::istream &is, const MgtProv &b)
      {
        return is >> (T) (b.value);
      }

      virtual std::vector<std::string> *getChildNames();

      /**
       * \brief   Function to set data to database
       */
      ClRcT setDb(std::string pxp = "", MgtDatabase *db = nullptr);

      /**
       * \brief   Function to get data from database
       */
      ClRcT getDb(std::string pxp = "", MgtDatabase *db = nullptr);

      /**
       *
       */
      virtual ClRcT write(MgtDatabase *db = nullptr, std::string xpath = "")
      {
        return setDb(xpath, db);
      }
      /**
       *
       */
      virtual ClRcT read(MgtDatabase *db = nullptr, std::string xpath = "")
      {
        return getDb(xpath, db);
      }

      virtual ClRcT setObj(const std::string &value);
    };

  template<class T>
    class ProvOperation : public SAFplus::TransactionOperation
    {
    protected:
      MgtProv<T> *mOwner;
      void *mData;

    public:
      ProvOperation()
      {
        mOwner = nullptr;
        mData = nullptr;
      }
      void setData(MgtProv<T> *owner, void *data, ClUint64T buffLen);
      virtual bool validate(SAFplus::Transaction& t);
      virtual void commit();
      virtual void abort();
    };

  /*
   * Implementation of ProvOperation class
   * G++ compiler: template function declarations and implementations must appear in the same file.
   */

  template<class T>
    void ProvOperation<T>::setData(MgtProv<T> *owner, void *data, ClUint64T buffLen)
    {
      mOwner = owner;
      mData = (void *) malloc(buffLen);

      if (!mData)
        return;

      memcpy(mData, data, buffLen);
    }

  template<class T>
    bool ProvOperation<T>::validate(SAFplus::Transaction& t)
    {
      if ((!mOwner) || (!mData))
        return false;

      return true;
    }

  template<class T>
    void ProvOperation<T>::commit()
    {
      if ((!mOwner) || (!mData))
        return;

      char *valstr = (char *) mData;
      deXMLize(valstr, mOwner, mOwner->value);

      mOwner->setDb();
      free(mData);
      mData = nullptr;
    }

  template<class T>
    void ProvOperation<T>::abort()
    {
      if ((!mOwner) || (!mData))
        return;

      free(mData);
      mData = nullptr;
    }
  /*
   * Implementation of MgtProv class
   * G++ compiler: template function declarations and implementations must appear in the same file.
   */

  template<class T>
  MgtProv<T>::MgtProv(const char* name) : MgtObject(name),value()
    {
      mValIndex = -1;
    }

  template<class T>
    MgtProv<T>::~MgtProv()
    {
    }

  template<class T>
  void MgtProv<T>::toString(std::stringstream& xmlString, int depth,SerializationOptions opts)
    {
      xmlString << "<" << tag;
      if (opts & MgtObject::SerializeNameAttribute)
        xmlString << " name=" << "\"" << getFullXpath(false) << "\"";
      if (opts & MgtObject::SerializePathAttribute)
        xmlString << " path=" << "\"" << getFullXpath() << "\"";
      xmlString << ">";
      xmlString << value;
      xmlString << "</" << tag << ">";
    }

  template<class T>
    std::string MgtProv<T>::strValue()
    {
      std::stringstream ss;
      ss << value;
      return ss.str();
    }

  template<class T>
    void MgtProv<T>::xset(const void *pBuffer, ClUint64T buffLen, SAFplus::Transaction& t)
    {
      if (!set((void *) pBuffer, buffLen, t))
        throw SAFplus::TransactionException(t);
    }

  template<class T>
    bool MgtProv<T>::set(const T& val, SAFplus::Transaction& t)
    {
      if (&t == &SAFplus::NO_TXN)
        {
          value = val;
          MgtObject *r = root();
          r->headRev = r->headRev + 1;
        }
      else
        {
          MgtObject *r = root();
          SimpleTxnOperation<T> *opt = new SimpleTxnOperation<T>(&value, val);
          ClUint32T newHeadRev = r->headRev + 1;
          SimpleTxnOperation<ClUint32T> *opt2 =
              new SimpleTxnOperation<ClUint32T>(&(r->headRev), newHeadRev);
          t.addOperation(opt);
          t.addOperation(opt2);
        }
      return true;
    }

  template<class T>
    ClBoolT MgtProv<T>::set(const void *pBuffer, ClUint64T buffLen, SAFplus::Transaction& t)
    {
      xmlChar *valstr, *namestr;
      int ret, nodetyp, depth;
      std::stringstream ss;
#ifndef SAFplus7
      logDebug("MGT", "OBJ", "Validate [%.*s]", (int) buffLen, (const char*)pBuffer);
#endif
      xmlTextReaderPtr reader = xmlReaderForMemory((const char*) pBuffer, buffLen, nullptr, nullptr, 0);
      if (!reader)
        {
          return CL_FALSE;
        }

      ret = xmlTextReaderRead(reader);
      if (ret <= 0)
        {
          xmlFreeTextReader(reader);
          return CL_FALSE;
        }

      namestr = (xmlChar *) xmlTextReaderConstName(reader);

      if (strcmp((char *) namestr, tag.c_str()))
        {
#ifndef SAFplus7
          logDebug("MGT","PROV","Name [%s], XML [%s]",tag.c_str(),(char *)namestr);
#endif
          xmlFreeTextReader(reader);
          return CL_FALSE;
        }

      ret = xmlTextReaderRead(reader);
      if (ret <= 0)
        {
          xmlFreeTextReader(reader);
          return CL_FALSE;
        }

      depth = xmlTextReaderDepth(reader);
      nodetyp = xmlTextReaderNodeType(reader);
      valstr = (xmlChar *) xmlTextReaderValue(reader);

      if ((nodetyp != XML_TEXT_NODE) || (depth != 1))
        {
          xmlFreeTextReader(reader);
          return CL_FALSE;
        }

      ProvOperation<T> *opt = new ProvOperation<T>;
      opt->setData(this, (void *) valstr, strlen((char *) valstr) + 1);
      MgtObject *r = root();
      ClUint32T newHeadRev = r->headRev + 1;
      SimpleTxnOperation<ClUint32T> *opt2 = new SimpleTxnOperation<ClUint32T>(&(r->headRev), newHeadRev);
      t.addOperation(opt);
      t.addOperation(opt2);

      xmlFree(valstr);
      xmlFreeTextReader(reader);
      return (opt->validate(t) && opt2->validate(t));
    }

  /*
   * Leaf doesn't have children
   */
  template<class T>
    std::vector<std::string> *MgtProv<T>::getChildNames()
    {
      return nullptr;
    }

  template<class T>
    ClRcT MgtProv<T>::setDb(std::string pxp, MgtDatabase *db)
    {
      //TODO: Temporary not support because of bug
      return CL_OK;
#if 0
      if (!loadDb)
      return CL_OK;

      std::string key;
      if (dataXPath.size() > 0)
        {
          key.assign(dataXPath);
        }
      else if(pxp.size() > 0)
        {
          key.assign(pxp);
          key.append(getFullXpath(false));
        }
      else
      key.assign(getFullXpath(true));

      std::stringstream ss;
      ss << value;
      if(db == nullptr)
        {
          db = MgtDatabase::getInstance();
        }

      return db->insertRecord(key, ss.str());
#endif
    }

  template<class T>
    ClRcT MgtProv<T>::getDb(std::string pxp, MgtDatabase *db)
    {
      if (!loadDb)
        return CL_OK;

      std::string key = getFullXpath();
      if (pxp.size() > 0)
        {
          key = getFullXpath(false);
          pxp.append(key);
          key = pxp;
        }
      if (db == nullptr)
        {
          db = MgtDatabase::getInstance();
        }

      dataXPath.assign(key);
      loadDb = true;

      std::string val;
      ClRcT rc = db->getRecord(key, val);
      if (CL_OK != rc)
        {
          return rc;
        }
      deXMLize(val, this, value);
      return rc;
    }

  template<class T>
    ClRcT MgtProv<T>::setObj(const std::string &val)
    {
      if (!config)
        {
        logDebug("MGT","PROV","attempt to set a non-config object [%s]",tag.c_str());
        return CL_ERR_BAD_OPERATION;
        }

      deXMLize(val, this, value);

      MgtObject *r = root();
      r->headRev = r->headRev + 1;

      return CL_OK;
    }

}
;
#endif /* CLMGTPROV_HPP_ */

/** \} */

