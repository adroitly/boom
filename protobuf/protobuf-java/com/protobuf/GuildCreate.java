// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: guild_create.proto

package com.protobuf;

public final class GuildCreate {
  private GuildCreate() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
  }
  public interface guild_create_requestOrBuilder extends
      // @@protoc_insertion_point(interface_extends:guild_create_request)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>required uint32 country = 1;</code>
     */
    boolean hasCountry();
    /**
     * <code>required uint32 country = 1;</code>
     */
    int getCountry();

    /**
     * <code>required uint32 flag = 2;</code>
     */
    boolean hasFlag();
    /**
     * <code>required uint32 flag = 2;</code>
     */
    int getFlag();

    /**
     * <code>required string name = 3;</code>
     */
    boolean hasName();
    /**
     * <code>required string name = 3;</code>
     */
    java.lang.String getName();
    /**
     * <code>required string name = 3;</code>
     */
    com.google.protobuf.ByteString
        getNameBytes();
  }
  /**
   * Protobuf type {@code guild_create_request}
   */
  public static final class guild_create_request extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:guild_create_request)
      guild_create_requestOrBuilder {
    // Use guild_create_request.newBuilder() to construct.
    private guild_create_request(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private guild_create_request(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final guild_create_request defaultInstance;
    public static guild_create_request getDefaultInstance() {
      return defaultInstance;
    }

    public guild_create_request getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private guild_create_request(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      initFields();
      int mutable_bitField0_ = 0;
      com.google.protobuf.UnknownFieldSet.Builder unknownFields =
          com.google.protobuf.UnknownFieldSet.newBuilder();
      try {
        boolean done = false;
        while (!done) {
          int tag = input.readTag();
          switch (tag) {
            case 0:
              done = true;
              break;
            default: {
              if (!parseUnknownField(input, unknownFields,
                                     extensionRegistry, tag)) {
                done = true;
              }
              break;
            }
            case 8: {
              bitField0_ |= 0x00000001;
              country_ = input.readUInt32();
              break;
            }
            case 16: {
              bitField0_ |= 0x00000002;
              flag_ = input.readUInt32();
              break;
            }
            case 26: {
              com.google.protobuf.ByteString bs = input.readBytes();
              bitField0_ |= 0x00000004;
              name_ = bs;
              break;
            }
          }
        }
      } catch (com.google.protobuf.InvalidProtocolBufferException e) {
        throw e.setUnfinishedMessage(this);
      } catch (java.io.IOException e) {
        throw new com.google.protobuf.InvalidProtocolBufferException(
            e.getMessage()).setUnfinishedMessage(this);
      } finally {
        this.unknownFields = unknownFields.build();
        makeExtensionsImmutable();
      }
    }
    public static final com.google.protobuf.Descriptors.Descriptor
        getDescriptor() {
      return com.protobuf.GuildCreate.internal_static_guild_create_request_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.GuildCreate.internal_static_guild_create_request_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.GuildCreate.guild_create_request.class, com.protobuf.GuildCreate.guild_create_request.Builder.class);
    }

    public static com.google.protobuf.Parser<guild_create_request> PARSER =
        new com.google.protobuf.AbstractParser<guild_create_request>() {
      public guild_create_request parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new guild_create_request(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<guild_create_request> getParserForType() {
      return PARSER;
    }

    private int bitField0_;
    public static final int COUNTRY_FIELD_NUMBER = 1;
    private int country_;
    /**
     * <code>required uint32 country = 1;</code>
     */
    public boolean hasCountry() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required uint32 country = 1;</code>
     */
    public int getCountry() {
      return country_;
    }

    public static final int FLAG_FIELD_NUMBER = 2;
    private int flag_;
    /**
     * <code>required uint32 flag = 2;</code>
     */
    public boolean hasFlag() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required uint32 flag = 2;</code>
     */
    public int getFlag() {
      return flag_;
    }

    public static final int NAME_FIELD_NUMBER = 3;
    private java.lang.Object name_;
    /**
     * <code>required string name = 3;</code>
     */
    public boolean hasName() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>required string name = 3;</code>
     */
    public java.lang.String getName() {
      java.lang.Object ref = name_;
      if (ref instanceof java.lang.String) {
        return (java.lang.String) ref;
      } else {
        com.google.protobuf.ByteString bs = 
            (com.google.protobuf.ByteString) ref;
        java.lang.String s = bs.toStringUtf8();
        if (bs.isValidUtf8()) {
          name_ = s;
        }
        return s;
      }
    }
    /**
     * <code>required string name = 3;</code>
     */
    public com.google.protobuf.ByteString
        getNameBytes() {
      java.lang.Object ref = name_;
      if (ref instanceof java.lang.String) {
        com.google.protobuf.ByteString b = 
            com.google.protobuf.ByteString.copyFromUtf8(
                (java.lang.String) ref);
        name_ = b;
        return b;
      } else {
        return (com.google.protobuf.ByteString) ref;
      }
    }

    private void initFields() {
      country_ = 0;
      flag_ = 0;
      name_ = "";
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      if (!hasCountry()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasFlag()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasName()) {
        memoizedIsInitialized = 0;
        return false;
      }
      memoizedIsInitialized = 1;
      return true;
    }

    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      getSerializedSize();
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        output.writeUInt32(1, country_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeUInt32(2, flag_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeBytes(3, getNameBytes());
      }
      getUnknownFields().writeTo(output);
    }

    private int memoizedSerializedSize = -1;
    public int getSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(1, country_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(2, flag_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeBytesSize(3, getNameBytes());
      }
      size += getUnknownFields().getSerializedSize();
      memoizedSerializedSize = size;
      return size;
    }

    private static final long serialVersionUID = 0L;
    @java.lang.Override
    protected java.lang.Object writeReplace()
        throws java.io.ObjectStreamException {
      return super.writeReplace();
    }

    public static com.protobuf.GuildCreate.guild_create_request parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.GuildCreate.guild_create_request parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.GuildCreate.guild_create_request prototype) {
      return newBuilder().mergeFrom(prototype);
    }
    public Builder toBuilder() { return newBuilder(this); }

    @java.lang.Override
    protected Builder newBuilderForType(
        com.google.protobuf.GeneratedMessage.BuilderParent parent) {
      Builder builder = new Builder(parent);
      return builder;
    }
    /**
     * Protobuf type {@code guild_create_request}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:guild_create_request)
        com.protobuf.GuildCreate.guild_create_requestOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.GuildCreate.internal_static_guild_create_request_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.GuildCreate.internal_static_guild_create_request_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.GuildCreate.guild_create_request.class, com.protobuf.GuildCreate.guild_create_request.Builder.class);
      }

      // Construct using com.protobuf.GuildCreate.guild_create_request.newBuilder()
      private Builder() {
        maybeForceBuilderInitialization();
      }

      private Builder(
          com.google.protobuf.GeneratedMessage.BuilderParent parent) {
        super(parent);
        maybeForceBuilderInitialization();
      }
      private void maybeForceBuilderInitialization() {
        if (com.google.protobuf.GeneratedMessage.alwaysUseFieldBuilders) {
        }
      }
      private static Builder create() {
        return new Builder();
      }

      public Builder clear() {
        super.clear();
        country_ = 0;
        bitField0_ = (bitField0_ & ~0x00000001);
        flag_ = 0;
        bitField0_ = (bitField0_ & ~0x00000002);
        name_ = "";
        bitField0_ = (bitField0_ & ~0x00000004);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.GuildCreate.internal_static_guild_create_request_descriptor;
      }

      public com.protobuf.GuildCreate.guild_create_request getDefaultInstanceForType() {
        return com.protobuf.GuildCreate.guild_create_request.getDefaultInstance();
      }

      public com.protobuf.GuildCreate.guild_create_request build() {
        com.protobuf.GuildCreate.guild_create_request result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.GuildCreate.guild_create_request buildPartial() {
        com.protobuf.GuildCreate.guild_create_request result = new com.protobuf.GuildCreate.guild_create_request(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.country_ = country_;
        if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
          to_bitField0_ |= 0x00000002;
        }
        result.flag_ = flag_;
        if (((from_bitField0_ & 0x00000004) == 0x00000004)) {
          to_bitField0_ |= 0x00000004;
        }
        result.name_ = name_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.GuildCreate.guild_create_request) {
          return mergeFrom((com.protobuf.GuildCreate.guild_create_request)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.GuildCreate.guild_create_request other) {
        if (other == com.protobuf.GuildCreate.guild_create_request.getDefaultInstance()) return this;
        if (other.hasCountry()) {
          setCountry(other.getCountry());
        }
        if (other.hasFlag()) {
          setFlag(other.getFlag());
        }
        if (other.hasName()) {
          bitField0_ |= 0x00000004;
          name_ = other.name_;
          onChanged();
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasCountry()) {
          
          return false;
        }
        if (!hasFlag()) {
          
          return false;
        }
        if (!hasName()) {
          
          return false;
        }
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.GuildCreate.guild_create_request parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.GuildCreate.guild_create_request) e.getUnfinishedMessage();
          throw e;
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private int country_ ;
      /**
       * <code>required uint32 country = 1;</code>
       */
      public boolean hasCountry() {
        return ((bitField0_ & 0x00000001) == 0x00000001);
      }
      /**
       * <code>required uint32 country = 1;</code>
       */
      public int getCountry() {
        return country_;
      }
      /**
       * <code>required uint32 country = 1;</code>
       */
      public Builder setCountry(int value) {
        bitField0_ |= 0x00000001;
        country_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 country = 1;</code>
       */
      public Builder clearCountry() {
        bitField0_ = (bitField0_ & ~0x00000001);
        country_ = 0;
        onChanged();
        return this;
      }

      private int flag_ ;
      /**
       * <code>required uint32 flag = 2;</code>
       */
      public boolean hasFlag() {
        return ((bitField0_ & 0x00000002) == 0x00000002);
      }
      /**
       * <code>required uint32 flag = 2;</code>
       */
      public int getFlag() {
        return flag_;
      }
      /**
       * <code>required uint32 flag = 2;</code>
       */
      public Builder setFlag(int value) {
        bitField0_ |= 0x00000002;
        flag_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 flag = 2;</code>
       */
      public Builder clearFlag() {
        bitField0_ = (bitField0_ & ~0x00000002);
        flag_ = 0;
        onChanged();
        return this;
      }

      private java.lang.Object name_ = "";
      /**
       * <code>required string name = 3;</code>
       */
      public boolean hasName() {
        return ((bitField0_ & 0x00000004) == 0x00000004);
      }
      /**
       * <code>required string name = 3;</code>
       */
      public java.lang.String getName() {
        java.lang.Object ref = name_;
        if (!(ref instanceof java.lang.String)) {
          com.google.protobuf.ByteString bs =
              (com.google.protobuf.ByteString) ref;
          java.lang.String s = bs.toStringUtf8();
          if (bs.isValidUtf8()) {
            name_ = s;
          }
          return s;
        } else {
          return (java.lang.String) ref;
        }
      }
      /**
       * <code>required string name = 3;</code>
       */
      public com.google.protobuf.ByteString
          getNameBytes() {
        java.lang.Object ref = name_;
        if (ref instanceof String) {
          com.google.protobuf.ByteString b = 
              com.google.protobuf.ByteString.copyFromUtf8(
                  (java.lang.String) ref);
          name_ = b;
          return b;
        } else {
          return (com.google.protobuf.ByteString) ref;
        }
      }
      /**
       * <code>required string name = 3;</code>
       */
      public Builder setName(
          java.lang.String value) {
        if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000004;
        name_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required string name = 3;</code>
       */
      public Builder clearName() {
        bitField0_ = (bitField0_ & ~0x00000004);
        name_ = getDefaultInstance().getName();
        onChanged();
        return this;
      }
      /**
       * <code>required string name = 3;</code>
       */
      public Builder setNameBytes(
          com.google.protobuf.ByteString value) {
        if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000004;
        name_ = value;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:guild_create_request)
    }

    static {
      defaultInstance = new guild_create_request(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:guild_create_request)
  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_guild_create_request_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_guild_create_request_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\022guild_create.proto\"C\n\024guild_create_req" +
      "uest\022\017\n\007country\030\001 \002(\r\022\014\n\004flag\030\002 \002(\r\022\014\n\004n" +
      "ame\030\003 \002(\tB\016\n\014com.protobuf"
    };
    com.google.protobuf.Descriptors.FileDescriptor.InternalDescriptorAssigner assigner =
        new com.google.protobuf.Descriptors.FileDescriptor.    InternalDescriptorAssigner() {
          public com.google.protobuf.ExtensionRegistry assignDescriptors(
              com.google.protobuf.Descriptors.FileDescriptor root) {
            descriptor = root;
            return null;
          }
        };
    com.google.protobuf.Descriptors.FileDescriptor
      .internalBuildGeneratedFileFrom(descriptorData,
        new com.google.protobuf.Descriptors.FileDescriptor[] {
        }, assigner);
    internal_static_guild_create_request_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_guild_create_request_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_guild_create_request_descriptor,
        new java.lang.String[] { "Country", "Flag", "Name", });
  }

  // @@protoc_insertion_point(outer_class_scope)
}
