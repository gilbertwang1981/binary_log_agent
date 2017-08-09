// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: protocol/configure.proto

#ifndef PROTOBUF_protocol_2fconfigure_2eproto__INCLUDED
#define PROTOBUF_protocol_2fconfigure_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace com {
namespace vip {
namespace local {
namespace cache {
namespace proto {
class ConfigObject;
class ConfigObjectDefaultTypeInternal;
extern ConfigObjectDefaultTypeInternal _ConfigObject_default_instance_;
}  // namespace proto
}  // namespace cache
}  // namespace local
}  // namespace vip
}  // namespace com

namespace com {
namespace vip {
namespace local {
namespace cache {
namespace proto {

namespace protobuf_protocol_2fconfigure_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_protocol_2fconfigure_2eproto

// ===================================================================

class ConfigObject : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:com.vip.local.cache.proto.ConfigObject) */ {
 public:
  ConfigObject();
  virtual ~ConfigObject();

  ConfigObject(const ConfigObject& from);

  inline ConfigObject& operator=(const ConfigObject& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ConfigObject& default_instance();

  static inline const ConfigObject* internal_default_instance() {
    return reinterpret_cast<const ConfigObject*>(
               &_ConfigObject_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(ConfigObject* other);

  // implements Message ----------------------------------------------

  inline ConfigObject* New() const PROTOBUF_FINAL { return New(NULL); }

  ConfigObject* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ConfigObject& from);
  void MergeFrom(const ConfigObject& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(ConfigObject* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string ip = 1;
  void clear_ip();
  static const int kIpFieldNumber = 1;
  const ::std::string& ip() const;
  void set_ip(const ::std::string& value);
  #if LANG_CXX11
  void set_ip(::std::string&& value);
  #endif
  void set_ip(const char* value);
  void set_ip(const char* value, size_t size);
  ::std::string* mutable_ip();
  ::std::string* release_ip();
  void set_allocated_ip(::std::string* ip);

  // string key = 3;
  void clear_key();
  static const int kKeyFieldNumber = 3;
  const ::std::string& key() const;
  void set_key(const ::std::string& value);
  #if LANG_CXX11
  void set_key(::std::string&& value);
  #endif
  void set_key(const char* value);
  void set_key(const char* value, size_t size);
  ::std::string* mutable_key();
  ::std::string* release_key();
  void set_allocated_key(::std::string* key);

  // string value = 4;
  void clear_value();
  static const int kValueFieldNumber = 4;
  const ::std::string& value() const;
  void set_value(const ::std::string& value);
  #if LANG_CXX11
  void set_value(::std::string&& value);
  #endif
  void set_value(const char* value);
  void set_value(const char* value, size_t size);
  ::std::string* mutable_value();
  ::std::string* release_value();
  void set_allocated_value(::std::string* value);

  // string extra = 5;
  void clear_extra();
  static const int kExtraFieldNumber = 5;
  const ::std::string& extra() const;
  void set_extra(const ::std::string& value);
  #if LANG_CXX11
  void set_extra(::std::string&& value);
  #endif
  void set_extra(const char* value);
  void set_extra(const char* value, size_t size);
  ::std::string* mutable_extra();
  ::std::string* release_extra();
  void set_allocated_extra(::std::string* extra);

  // uint64 timestamp = 6;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 6;
  ::google::protobuf::uint64 timestamp() const;
  void set_timestamp(::google::protobuf::uint64 value);

  // uint32 opType = 2;
  void clear_optype();
  static const int kOpTypeFieldNumber = 2;
  ::google::protobuf::uint32 optype() const;
  void set_optype(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:com.vip.local.cache.proto.ConfigObject)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr ip_;
  ::google::protobuf::internal::ArenaStringPtr key_;
  ::google::protobuf::internal::ArenaStringPtr value_;
  ::google::protobuf::internal::ArenaStringPtr extra_;
  ::google::protobuf::uint64 timestamp_;
  ::google::protobuf::uint32 optype_;
  mutable int _cached_size_;
  friend struct protobuf_protocol_2fconfigure_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ConfigObject

// string ip = 1;
inline void ConfigObject::clear_ip() {
  ip_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ConfigObject::ip() const {
  // @@protoc_insertion_point(field_get:com.vip.local.cache.proto.ConfigObject.ip)
  return ip_.GetNoArena();
}
inline void ConfigObject::set_ip(const ::std::string& value) {
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:com.vip.local.cache.proto.ConfigObject.ip)
}
#if LANG_CXX11
inline void ConfigObject::set_ip(::std::string&& value) {
  
  ip_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:com.vip.local.cache.proto.ConfigObject.ip)
}
#endif
inline void ConfigObject::set_ip(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:com.vip.local.cache.proto.ConfigObject.ip)
}
inline void ConfigObject::set_ip(const char* value, size_t size) {
  
  ip_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:com.vip.local.cache.proto.ConfigObject.ip)
}
inline ::std::string* ConfigObject::mutable_ip() {
  
  // @@protoc_insertion_point(field_mutable:com.vip.local.cache.proto.ConfigObject.ip)
  return ip_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ConfigObject::release_ip() {
  // @@protoc_insertion_point(field_release:com.vip.local.cache.proto.ConfigObject.ip)
  
  return ip_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ConfigObject::set_allocated_ip(::std::string* ip) {
  if (ip != NULL) {
    
  } else {
    
  }
  ip_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ip);
  // @@protoc_insertion_point(field_set_allocated:com.vip.local.cache.proto.ConfigObject.ip)
}

// uint32 opType = 2;
inline void ConfigObject::clear_optype() {
  optype_ = 0u;
}
inline ::google::protobuf::uint32 ConfigObject::optype() const {
  // @@protoc_insertion_point(field_get:com.vip.local.cache.proto.ConfigObject.opType)
  return optype_;
}
inline void ConfigObject::set_optype(::google::protobuf::uint32 value) {
  
  optype_ = value;
  // @@protoc_insertion_point(field_set:com.vip.local.cache.proto.ConfigObject.opType)
}

// string key = 3;
inline void ConfigObject::clear_key() {
  key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ConfigObject::key() const {
  // @@protoc_insertion_point(field_get:com.vip.local.cache.proto.ConfigObject.key)
  return key_.GetNoArena();
}
inline void ConfigObject::set_key(const ::std::string& value) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:com.vip.local.cache.proto.ConfigObject.key)
}
#if LANG_CXX11
inline void ConfigObject::set_key(::std::string&& value) {
  
  key_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:com.vip.local.cache.proto.ConfigObject.key)
}
#endif
inline void ConfigObject::set_key(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:com.vip.local.cache.proto.ConfigObject.key)
}
inline void ConfigObject::set_key(const char* value, size_t size) {
  
  key_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:com.vip.local.cache.proto.ConfigObject.key)
}
inline ::std::string* ConfigObject::mutable_key() {
  
  // @@protoc_insertion_point(field_mutable:com.vip.local.cache.proto.ConfigObject.key)
  return key_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ConfigObject::release_key() {
  // @@protoc_insertion_point(field_release:com.vip.local.cache.proto.ConfigObject.key)
  
  return key_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ConfigObject::set_allocated_key(::std::string* key) {
  if (key != NULL) {
    
  } else {
    
  }
  key_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), key);
  // @@protoc_insertion_point(field_set_allocated:com.vip.local.cache.proto.ConfigObject.key)
}

// string value = 4;
inline void ConfigObject::clear_value() {
  value_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ConfigObject::value() const {
  // @@protoc_insertion_point(field_get:com.vip.local.cache.proto.ConfigObject.value)
  return value_.GetNoArena();
}
inline void ConfigObject::set_value(const ::std::string& value) {
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:com.vip.local.cache.proto.ConfigObject.value)
}
#if LANG_CXX11
inline void ConfigObject::set_value(::std::string&& value) {
  
  value_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:com.vip.local.cache.proto.ConfigObject.value)
}
#endif
inline void ConfigObject::set_value(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:com.vip.local.cache.proto.ConfigObject.value)
}
inline void ConfigObject::set_value(const char* value, size_t size) {
  
  value_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:com.vip.local.cache.proto.ConfigObject.value)
}
inline ::std::string* ConfigObject::mutable_value() {
  
  // @@protoc_insertion_point(field_mutable:com.vip.local.cache.proto.ConfigObject.value)
  return value_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ConfigObject::release_value() {
  // @@protoc_insertion_point(field_release:com.vip.local.cache.proto.ConfigObject.value)
  
  return value_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ConfigObject::set_allocated_value(::std::string* value) {
  if (value != NULL) {
    
  } else {
    
  }
  value_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set_allocated:com.vip.local.cache.proto.ConfigObject.value)
}

// string extra = 5;
inline void ConfigObject::clear_extra() {
  extra_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ConfigObject::extra() const {
  // @@protoc_insertion_point(field_get:com.vip.local.cache.proto.ConfigObject.extra)
  return extra_.GetNoArena();
}
inline void ConfigObject::set_extra(const ::std::string& value) {
  
  extra_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:com.vip.local.cache.proto.ConfigObject.extra)
}
#if LANG_CXX11
inline void ConfigObject::set_extra(::std::string&& value) {
  
  extra_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:com.vip.local.cache.proto.ConfigObject.extra)
}
#endif
inline void ConfigObject::set_extra(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  extra_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:com.vip.local.cache.proto.ConfigObject.extra)
}
inline void ConfigObject::set_extra(const char* value, size_t size) {
  
  extra_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:com.vip.local.cache.proto.ConfigObject.extra)
}
inline ::std::string* ConfigObject::mutable_extra() {
  
  // @@protoc_insertion_point(field_mutable:com.vip.local.cache.proto.ConfigObject.extra)
  return extra_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ConfigObject::release_extra() {
  // @@protoc_insertion_point(field_release:com.vip.local.cache.proto.ConfigObject.extra)
  
  return extra_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ConfigObject::set_allocated_extra(::std::string* extra) {
  if (extra != NULL) {
    
  } else {
    
  }
  extra_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), extra);
  // @@protoc_insertion_point(field_set_allocated:com.vip.local.cache.proto.ConfigObject.extra)
}

// uint64 timestamp = 6;
inline void ConfigObject::clear_timestamp() {
  timestamp_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 ConfigObject::timestamp() const {
  // @@protoc_insertion_point(field_get:com.vip.local.cache.proto.ConfigObject.timestamp)
  return timestamp_;
}
inline void ConfigObject::set_timestamp(::google::protobuf::uint64 value) {
  
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:com.vip.local.cache.proto.ConfigObject.timestamp)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace proto
}  // namespace cache
}  // namespace local
}  // namespace vip
}  // namespace com

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_protocol_2fconfigure_2eproto__INCLUDED
