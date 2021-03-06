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
 *  \brief Header file of the MgtIdentifier class which provides APIs to manage MGT "instance identifier" objects
 *  \ingroup mgt
 */

/**
 *  \addtogroup mgt
 *  \{
 */
#pragma once
#ifndef CLMGTIDENTIFIER_HXX_
#define CLMGTIDENTIFIER_HXX_

#include "clMgtProv.hxx"
#include "clMgtRoot.hxx"
namespace SAFplus
{
  template <class T>
  class MgtIdentifier : public MgtObject
  {
  public:
      /**
       *  Value of the "MgtIdentifier" object
       */
      T value;

      std::string ref;

  public:
    MgtIdentifier(const char* name);
    virtual ~MgtIdentifier();

    virtual void toString(std::stringstream& xmlString, int depth=SAFplusI::MgtToStringRecursionDepth, SerializationOptions opts=SerializeNoOptions);
    virtual std::string strValue();

    /**
     * \brief   Define basic assignment operator
     */
    MgtIdentifier<T>& operator = (const T& val)
    {
        value = val;
        return *this;
    }
    /**
     * \brief   Define basic access (type cast) operator
     */
    operator T& ()
    {
      if (value==NULL) updateReference();  // was not loaded the first time, try to reresolve.  TODO: consider the efficiency of this 
      return value;
    }
    /**
     * \brief   Define basic comparison
     */
    bool operator == (const T& val) { return value==val; }

    /**
     * \brief   Virtual function to validate object data
     */
    virtual ClBoolT set(void *pBuffer, ClUint64T buffLen, SAFplus::Transaction& t);

    virtual ClRcT write(MgtDatabase* db, std::string xpt = "")
    {
      return CL_OK;
    }
    virtual ClRcT read(MgtDatabase *db, std::string xpt = "")
    {
      std::string key = getFullXpath();
      if (xpt.size() > 0)
        {
          key = getFullXpath(false);
          xpt.append(key);
          key = xpt;
        }

      if (db == nullptr)
        {
          db = MgtDatabase::getInstance();
        }

      dataXPath.assign(key);
      loadDb = true;

      std::string val;

      if (CL_OK == db->getRecord(key, val))
        {
          ref = val;
          MgtRoot *mgtRoot = MgtRoot::getInstance();
          mgtRoot->addReference(this);
        }

      return CL_OK;
    }

    //? Resolve this reference to a pointer if it is not yet resolved.  This can happen because this object may be loaded from the database before the object it points to is created.
    void updateReference()
    {
      MgtObject *root = this->root();
      if(ref.length() > 0)
        {
          MgtObject *obj = root->lookUpMgtObject(typeid(T).name(), ref);
          if (obj)
            value = (T)obj;
          else
            {
              logWarning("MGT", "READ", "Object [%s] contains unresolved management tree reference [%s]", getFullXpath(true).c_str(), ref.c_str());
            }
        }
    }

  };

  /*
   * Implementation of MgtIdentifier class
   * G++ compiler: template function declarations and implementations must appear in the same file.
   */

  template <class T>
  MgtIdentifier<T>::MgtIdentifier(const char* name) : MgtObject(name)
  {
    value = nullptr;
  }

  template <class T>
  MgtIdentifier<T>::~MgtIdentifier()
  {}

  template <class T>
  ClBoolT MgtIdentifier<T>::set( void *pBuffer, ClUint64T buffLen, SAFplus::Transaction& t)
  {
    return CL_FALSE;
  }

  template <class T>
  void MgtIdentifier<T>::toString(std::stringstream& xmlString, int depth, SerializationOptions opts)
  {
      if (value == nullptr)
          return;

      xmlString << "<";
      xmlString << tag << ">";
      MgtObject *obj = dynamic_cast<MgtObject *>(value);
      if (obj)
          xmlString << value->getFullXpath();
      xmlString << "</" << tag << ">";
  }

  template <class T>
  std::string MgtIdentifier<T>::strValue()
  {
      std::stringstream ss;

      if (value == nullptr)
          return ss.str();

      MgtObject *obj = dynamic_cast<MgtObject *>(value);
      if (obj)
          ss << value->getFullXpath();
      return ss.str();
  }
}
#endif /* CLMGTIDENTIFIER_HXX_ */

/** \} */

