// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: amfRpc.proto

#ifndef PROTOBUF_amfRpc_2eproto__INCLUDED
#define PROTOBUF_amfRpc_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "SAFplusPBExt.pb.h"
// @@protoc_insertion_point(includes)

namespace SAFplus {
namespace Rpc {
namespace amfRpc {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_amfRpc_2eproto();
void protobuf_AssignDesc_amfRpc_2eproto();
void protobuf_ShutdownFile_amfRpc_2eproto();

class StartComponentRequest;
class StartComponentResponse;
class StopComponentRequest;
class StopComponentResponse;
class ProcessInfoRequest;
class ProcessInfoResponse;
class ProcessFailedRequest;
class ProcessFailedResponse;

// ===================================================================

class StartComponentRequest : public ::google::protobuf::Message {
 public:
  StartComponentRequest();
  virtual ~StartComponentRequest();

  StartComponentRequest(const StartComponentRequest& from);

  inline StartComponentRequest& operator=(const StartComponentRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const StartComponentRequest& default_instance();

  void Swap(StartComponentRequest* other);

  // implements Message ----------------------------------------------

  StartComponentRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StartComponentRequest& from);
  void MergeFrom(const StartComponentRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional string command = 2;
  inline bool has_command() const;
  inline void clear_command();
  static const int kCommandFieldNumber = 2;
  inline const ::std::string& command() const;
  inline void set_command(const ::std::string& value);
  inline void set_command(const char* value);
  inline void set_command(const char* value, size_t size);
  inline ::std::string* mutable_command();
  inline ::std::string* release_command();
  inline void set_allocated_command(::std::string* command);

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(StartComponentRequest)
  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.amfRpc.StartComponentRequest)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_command();
  inline void clear_has_command();

  ::google::protobuf::internal::ExtensionSet _extensions_;

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::std::string* command_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_amfRpc_2eproto();
  friend void protobuf_AssignDesc_amfRpc_2eproto();
  friend void protobuf_ShutdownFile_amfRpc_2eproto();

  void InitAsDefaultInstance();
  static StartComponentRequest* default_instance_;
};
// -------------------------------------------------------------------

class StartComponentResponse : public ::google::protobuf::Message {
 public:
  StartComponentResponse();
  virtual ~StartComponentResponse();

  StartComponentResponse(const StartComponentResponse& from);

  inline StartComponentResponse& operator=(const StartComponentResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const StartComponentResponse& default_instance();

  void Swap(StartComponentResponse* other);

  // implements Message ----------------------------------------------

  StartComponentResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StartComponentResponse& from);
  void MergeFrom(const StartComponentResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 err = 1;
  inline bool has_err() const;
  inline void clear_err();
  static const int kErrFieldNumber = 1;
  inline ::google::protobuf::int32 err() const;
  inline void set_err(::google::protobuf::int32 value);

  // optional int32 pid = 2;
  inline bool has_pid() const;
  inline void clear_pid();
  static const int kPidFieldNumber = 2;
  inline ::google::protobuf::int32 pid() const;
  inline void set_pid(::google::protobuf::int32 value);

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(StartComponentResponse)
  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.amfRpc.StartComponentResponse)
 private:
  inline void set_has_err();
  inline void clear_has_err();
  inline void set_has_pid();
  inline void clear_has_pid();

  ::google::protobuf::internal::ExtensionSet _extensions_;

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 err_;
  ::google::protobuf::int32 pid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_amfRpc_2eproto();
  friend void protobuf_AssignDesc_amfRpc_2eproto();
  friend void protobuf_ShutdownFile_amfRpc_2eproto();

  void InitAsDefaultInstance();
  static StartComponentResponse* default_instance_;
};
// -------------------------------------------------------------------

class StopComponentRequest : public ::google::protobuf::Message {
 public:
  StopComponentRequest();
  virtual ~StopComponentRequest();

  StopComponentRequest(const StopComponentRequest& from);

  inline StopComponentRequest& operator=(const StopComponentRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const StopComponentRequest& default_instance();

  void Swap(StopComponentRequest* other);

  // implements Message ----------------------------------------------

  StopComponentRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StopComponentRequest& from);
  void MergeFrom(const StopComponentRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 pid = 1;
  inline bool has_pid() const;
  inline void clear_pid();
  static const int kPidFieldNumber = 1;
  inline ::google::protobuf::int32 pid() const;
  inline void set_pid(::google::protobuf::int32 value);

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(StopComponentRequest)
  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.amfRpc.StopComponentRequest)
 private:
  inline void set_has_pid();
  inline void clear_has_pid();

  ::google::protobuf::internal::ExtensionSet _extensions_;

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 pid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_amfRpc_2eproto();
  friend void protobuf_AssignDesc_amfRpc_2eproto();
  friend void protobuf_ShutdownFile_amfRpc_2eproto();

  void InitAsDefaultInstance();
  static StopComponentRequest* default_instance_;
};
// -------------------------------------------------------------------

class StopComponentResponse : public ::google::protobuf::Message {
 public:
  StopComponentResponse();
  virtual ~StopComponentResponse();

  StopComponentResponse(const StopComponentResponse& from);

  inline StopComponentResponse& operator=(const StopComponentResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const StopComponentResponse& default_instance();

  void Swap(StopComponentResponse* other);

  // implements Message ----------------------------------------------

  StopComponentResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StopComponentResponse& from);
  void MergeFrom(const StopComponentResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 err = 1;
  inline bool has_err() const;
  inline void clear_err();
  static const int kErrFieldNumber = 1;
  inline ::google::protobuf::int32 err() const;
  inline void set_err(::google::protobuf::int32 value);

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(StopComponentResponse)
  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.amfRpc.StopComponentResponse)
 private:
  inline void set_has_err();
  inline void clear_has_err();

  ::google::protobuf::internal::ExtensionSet _extensions_;

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 err_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_amfRpc_2eproto();
  friend void protobuf_AssignDesc_amfRpc_2eproto();
  friend void protobuf_ShutdownFile_amfRpc_2eproto();

  void InitAsDefaultInstance();
  static StopComponentResponse* default_instance_;
};
// -------------------------------------------------------------------

class ProcessInfoRequest : public ::google::protobuf::Message {
 public:
  ProcessInfoRequest();
  virtual ~ProcessInfoRequest();

  ProcessInfoRequest(const ProcessInfoRequest& from);

  inline ProcessInfoRequest& operator=(const ProcessInfoRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProcessInfoRequest& default_instance();

  void Swap(ProcessInfoRequest* other);

  // implements Message ----------------------------------------------

  ProcessInfoRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProcessInfoRequest& from);
  void MergeFrom(const ProcessInfoRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 pid = 1;
  inline bool has_pid() const;
  inline void clear_pid();
  static const int kPidFieldNumber = 1;
  inline ::google::protobuf::int32 pid() const;
  inline void set_pid(::google::protobuf::int32 value);

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(ProcessInfoRequest)
  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.amfRpc.ProcessInfoRequest)
 private:
  inline void set_has_pid();
  inline void clear_has_pid();

  ::google::protobuf::internal::ExtensionSet _extensions_;

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 pid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_amfRpc_2eproto();
  friend void protobuf_AssignDesc_amfRpc_2eproto();
  friend void protobuf_ShutdownFile_amfRpc_2eproto();

  void InitAsDefaultInstance();
  static ProcessInfoRequest* default_instance_;
};
// -------------------------------------------------------------------

class ProcessInfoResponse : public ::google::protobuf::Message {
 public:
  ProcessInfoResponse();
  virtual ~ProcessInfoResponse();

  ProcessInfoResponse(const ProcessInfoResponse& from);

  inline ProcessInfoResponse& operator=(const ProcessInfoResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProcessInfoResponse& default_instance();

  void Swap(ProcessInfoResponse* other);

  // implements Message ----------------------------------------------

  ProcessInfoResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProcessInfoResponse& from);
  void MergeFrom(const ProcessInfoResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional bool running = 1;
  inline bool has_running() const;
  inline void clear_running();
  static const int kRunningFieldNumber = 1;
  inline bool running() const;
  inline void set_running(bool value);

  // optional string command = 2;
  inline bool has_command() const;
  inline void clear_command();
  static const int kCommandFieldNumber = 2;
  inline const ::std::string& command() const;
  inline void set_command(const ::std::string& value);
  inline void set_command(const char* value);
  inline void set_command(const char* value, size_t size);
  inline ::std::string* mutable_command();
  inline ::std::string* release_command();
  inline void set_allocated_command(::std::string* command);

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(ProcessInfoResponse)
  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.amfRpc.ProcessInfoResponse)
 private:
  inline void set_has_running();
  inline void clear_has_running();
  inline void set_has_command();
  inline void clear_has_command();

  ::google::protobuf::internal::ExtensionSet _extensions_;

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* command_;
  bool running_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_amfRpc_2eproto();
  friend void protobuf_AssignDesc_amfRpc_2eproto();
  friend void protobuf_ShutdownFile_amfRpc_2eproto();

  void InitAsDefaultInstance();
  static ProcessInfoResponse* default_instance_;
};
// -------------------------------------------------------------------

class ProcessFailedRequest : public ::google::protobuf::Message {
 public:
  ProcessFailedRequest();
  virtual ~ProcessFailedRequest();

  ProcessFailedRequest(const ProcessFailedRequest& from);

  inline ProcessFailedRequest& operator=(const ProcessFailedRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProcessFailedRequest& default_instance();

  void Swap(ProcessFailedRequest* other);

  // implements Message ----------------------------------------------

  ProcessFailedRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProcessFailedRequest& from);
  void MergeFrom(const ProcessFailedRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 pid = 1;
  inline bool has_pid() const;
  inline void clear_pid();
  static const int kPidFieldNumber = 1;
  inline ::google::protobuf::int32 pid() const;
  inline void set_pid(::google::protobuf::int32 value);

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(ProcessFailedRequest)
  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.amfRpc.ProcessFailedRequest)
 private:
  inline void set_has_pid();
  inline void clear_has_pid();

  ::google::protobuf::internal::ExtensionSet _extensions_;

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 pid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_amfRpc_2eproto();
  friend void protobuf_AssignDesc_amfRpc_2eproto();
  friend void protobuf_ShutdownFile_amfRpc_2eproto();

  void InitAsDefaultInstance();
  static ProcessFailedRequest* default_instance_;
};
// -------------------------------------------------------------------

class ProcessFailedResponse : public ::google::protobuf::Message {
 public:
  ProcessFailedResponse();
  virtual ~ProcessFailedResponse();

  ProcessFailedResponse(const ProcessFailedResponse& from);

  inline ProcessFailedResponse& operator=(const ProcessFailedResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProcessFailedResponse& default_instance();

  void Swap(ProcessFailedResponse* other);

  // implements Message ----------------------------------------------

  ProcessFailedResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProcessFailedResponse& from);
  void MergeFrom(const ProcessFailedResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 err = 1;
  inline bool has_err() const;
  inline void clear_err();
  static const int kErrFieldNumber = 1;
  inline ::google::protobuf::int32 err() const;
  inline void set_err(::google::protobuf::int32 value);

  GOOGLE_PROTOBUF_EXTENSION_ACCESSORS(ProcessFailedResponse)
  // @@protoc_insertion_point(class_scope:SAFplus.Rpc.amfRpc.ProcessFailedResponse)
 private:
  inline void set_has_err();
  inline void clear_has_err();

  ::google::protobuf::internal::ExtensionSet _extensions_;

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 err_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_amfRpc_2eproto();
  friend void protobuf_AssignDesc_amfRpc_2eproto();
  friend void protobuf_ShutdownFile_amfRpc_2eproto();

  void InitAsDefaultInstance();
  static ProcessFailedResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// StartComponentRequest

// optional string name = 1;
inline bool StartComponentRequest::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void StartComponentRequest::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void StartComponentRequest::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void StartComponentRequest::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& StartComponentRequest::name() const {
  return *name_;
}
inline void StartComponentRequest::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void StartComponentRequest::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void StartComponentRequest::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* StartComponentRequest::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* StartComponentRequest::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void StartComponentRequest::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional string command = 2;
inline bool StartComponentRequest::has_command() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void StartComponentRequest::set_has_command() {
  _has_bits_[0] |= 0x00000002u;
}
inline void StartComponentRequest::clear_has_command() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void StartComponentRequest::clear_command() {
  if (command_ != &::google::protobuf::internal::kEmptyString) {
    command_->clear();
  }
  clear_has_command();
}
inline const ::std::string& StartComponentRequest::command() const {
  return *command_;
}
inline void StartComponentRequest::set_command(const ::std::string& value) {
  set_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    command_ = new ::std::string;
  }
  command_->assign(value);
}
inline void StartComponentRequest::set_command(const char* value) {
  set_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    command_ = new ::std::string;
  }
  command_->assign(value);
}
inline void StartComponentRequest::set_command(const char* value, size_t size) {
  set_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    command_ = new ::std::string;
  }
  command_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* StartComponentRequest::mutable_command() {
  set_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    command_ = new ::std::string;
  }
  return command_;
}
inline ::std::string* StartComponentRequest::release_command() {
  clear_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = command_;
    command_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void StartComponentRequest::set_allocated_command(::std::string* command) {
  if (command_ != &::google::protobuf::internal::kEmptyString) {
    delete command_;
  }
  if (command) {
    set_has_command();
    command_ = command;
  } else {
    clear_has_command();
    command_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// StartComponentResponse

// optional int32 err = 1;
inline bool StartComponentResponse::has_err() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void StartComponentResponse::set_has_err() {
  _has_bits_[0] |= 0x00000001u;
}
inline void StartComponentResponse::clear_has_err() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void StartComponentResponse::clear_err() {
  err_ = 0;
  clear_has_err();
}
inline ::google::protobuf::int32 StartComponentResponse::err() const {
  return err_;
}
inline void StartComponentResponse::set_err(::google::protobuf::int32 value) {
  set_has_err();
  err_ = value;
}

// optional int32 pid = 2;
inline bool StartComponentResponse::has_pid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void StartComponentResponse::set_has_pid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void StartComponentResponse::clear_has_pid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void StartComponentResponse::clear_pid() {
  pid_ = 0;
  clear_has_pid();
}
inline ::google::protobuf::int32 StartComponentResponse::pid() const {
  return pid_;
}
inline void StartComponentResponse::set_pid(::google::protobuf::int32 value) {
  set_has_pid();
  pid_ = value;
}

// -------------------------------------------------------------------

// StopComponentRequest

// optional int32 pid = 1;
inline bool StopComponentRequest::has_pid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void StopComponentRequest::set_has_pid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void StopComponentRequest::clear_has_pid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void StopComponentRequest::clear_pid() {
  pid_ = 0;
  clear_has_pid();
}
inline ::google::protobuf::int32 StopComponentRequest::pid() const {
  return pid_;
}
inline void StopComponentRequest::set_pid(::google::protobuf::int32 value) {
  set_has_pid();
  pid_ = value;
}

// -------------------------------------------------------------------

// StopComponentResponse

// optional int32 err = 1;
inline bool StopComponentResponse::has_err() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void StopComponentResponse::set_has_err() {
  _has_bits_[0] |= 0x00000001u;
}
inline void StopComponentResponse::clear_has_err() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void StopComponentResponse::clear_err() {
  err_ = 0;
  clear_has_err();
}
inline ::google::protobuf::int32 StopComponentResponse::err() const {
  return err_;
}
inline void StopComponentResponse::set_err(::google::protobuf::int32 value) {
  set_has_err();
  err_ = value;
}

// -------------------------------------------------------------------

// ProcessInfoRequest

// optional int32 pid = 1;
inline bool ProcessInfoRequest::has_pid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProcessInfoRequest::set_has_pid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProcessInfoRequest::clear_has_pid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProcessInfoRequest::clear_pid() {
  pid_ = 0;
  clear_has_pid();
}
inline ::google::protobuf::int32 ProcessInfoRequest::pid() const {
  return pid_;
}
inline void ProcessInfoRequest::set_pid(::google::protobuf::int32 value) {
  set_has_pid();
  pid_ = value;
}

// -------------------------------------------------------------------

// ProcessInfoResponse

// optional bool running = 1;
inline bool ProcessInfoResponse::has_running() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProcessInfoResponse::set_has_running() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProcessInfoResponse::clear_has_running() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProcessInfoResponse::clear_running() {
  running_ = false;
  clear_has_running();
}
inline bool ProcessInfoResponse::running() const {
  return running_;
}
inline void ProcessInfoResponse::set_running(bool value) {
  set_has_running();
  running_ = value;
}

// optional string command = 2;
inline bool ProcessInfoResponse::has_command() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProcessInfoResponse::set_has_command() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProcessInfoResponse::clear_has_command() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProcessInfoResponse::clear_command() {
  if (command_ != &::google::protobuf::internal::kEmptyString) {
    command_->clear();
  }
  clear_has_command();
}
inline const ::std::string& ProcessInfoResponse::command() const {
  return *command_;
}
inline void ProcessInfoResponse::set_command(const ::std::string& value) {
  set_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    command_ = new ::std::string;
  }
  command_->assign(value);
}
inline void ProcessInfoResponse::set_command(const char* value) {
  set_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    command_ = new ::std::string;
  }
  command_->assign(value);
}
inline void ProcessInfoResponse::set_command(const char* value, size_t size) {
  set_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    command_ = new ::std::string;
  }
  command_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ProcessInfoResponse::mutable_command() {
  set_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    command_ = new ::std::string;
  }
  return command_;
}
inline ::std::string* ProcessInfoResponse::release_command() {
  clear_has_command();
  if (command_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = command_;
    command_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ProcessInfoResponse::set_allocated_command(::std::string* command) {
  if (command_ != &::google::protobuf::internal::kEmptyString) {
    delete command_;
  }
  if (command) {
    set_has_command();
    command_ = command;
  } else {
    clear_has_command();
    command_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// ProcessFailedRequest

// optional int32 pid = 1;
inline bool ProcessFailedRequest::has_pid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProcessFailedRequest::set_has_pid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProcessFailedRequest::clear_has_pid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProcessFailedRequest::clear_pid() {
  pid_ = 0;
  clear_has_pid();
}
inline ::google::protobuf::int32 ProcessFailedRequest::pid() const {
  return pid_;
}
inline void ProcessFailedRequest::set_pid(::google::protobuf::int32 value) {
  set_has_pid();
  pid_ = value;
}

// -------------------------------------------------------------------

// ProcessFailedResponse

// optional int32 err = 1;
inline bool ProcessFailedResponse::has_err() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProcessFailedResponse::set_has_err() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProcessFailedResponse::clear_has_err() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProcessFailedResponse::clear_err() {
  err_ = 0;
  clear_has_err();
}
inline ::google::protobuf::int32 ProcessFailedResponse::err() const {
  return err_;
}
inline void ProcessFailedResponse::set_err(::google::protobuf::int32 value) {
  set_has_err();
  err_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace amfRpc
}  // namespace Rpc
}  // namespace SAFplus

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_amfRpc_2eproto__INCLUDED
