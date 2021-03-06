// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: army_promote.proto

package com.protobuf;

public final class ArmyPromote {
  private ArmyPromote() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
  }
  public interface army_promote_requestOrBuilder extends
      // @@protoc_insertion_point(interface_extends:army_promote_request)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>required uint32 army_id = 1;</code>
     */
    boolean hasArmyId();
    /**
     * <code>required uint32 army_id = 1;</code>
     */
    int getArmyId();
  }
  /**
   * Protobuf type {@code army_promote_request}
   */
  public static final class army_promote_request extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:army_promote_request)
      army_promote_requestOrBuilder {
    // Use army_promote_request.newBuilder() to construct.
    private army_promote_request(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private army_promote_request(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final army_promote_request defaultInstance;
    public static army_promote_request getDefaultInstance() {
      return defaultInstance;
    }

    public army_promote_request getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private army_promote_request(
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
              armyId_ = input.readUInt32();
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
      return com.protobuf.ArmyPromote.internal_static_army_promote_request_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.ArmyPromote.internal_static_army_promote_request_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.ArmyPromote.army_promote_request.class, com.protobuf.ArmyPromote.army_promote_request.Builder.class);
    }

    public static com.google.protobuf.Parser<army_promote_request> PARSER =
        new com.google.protobuf.AbstractParser<army_promote_request>() {
      public army_promote_request parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new army_promote_request(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<army_promote_request> getParserForType() {
      return PARSER;
    }

    private int bitField0_;
    public static final int ARMY_ID_FIELD_NUMBER = 1;
    private int armyId_;
    /**
     * <code>required uint32 army_id = 1;</code>
     */
    public boolean hasArmyId() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required uint32 army_id = 1;</code>
     */
    public int getArmyId() {
      return armyId_;
    }

    private void initFields() {
      armyId_ = 0;
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      if (!hasArmyId()) {
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
        output.writeUInt32(1, armyId_);
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
          .computeUInt32Size(1, armyId_);
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

    public static com.protobuf.ArmyPromote.army_promote_request parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyPromote.army_promote_request parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.ArmyPromote.army_promote_request prototype) {
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
     * Protobuf type {@code army_promote_request}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:army_promote_request)
        com.protobuf.ArmyPromote.army_promote_requestOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.ArmyPromote.internal_static_army_promote_request_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.ArmyPromote.internal_static_army_promote_request_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.ArmyPromote.army_promote_request.class, com.protobuf.ArmyPromote.army_promote_request.Builder.class);
      }

      // Construct using com.protobuf.ArmyPromote.army_promote_request.newBuilder()
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
        armyId_ = 0;
        bitField0_ = (bitField0_ & ~0x00000001);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.ArmyPromote.internal_static_army_promote_request_descriptor;
      }

      public com.protobuf.ArmyPromote.army_promote_request getDefaultInstanceForType() {
        return com.protobuf.ArmyPromote.army_promote_request.getDefaultInstance();
      }

      public com.protobuf.ArmyPromote.army_promote_request build() {
        com.protobuf.ArmyPromote.army_promote_request result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.ArmyPromote.army_promote_request buildPartial() {
        com.protobuf.ArmyPromote.army_promote_request result = new com.protobuf.ArmyPromote.army_promote_request(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.armyId_ = armyId_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.ArmyPromote.army_promote_request) {
          return mergeFrom((com.protobuf.ArmyPromote.army_promote_request)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.ArmyPromote.army_promote_request other) {
        if (other == com.protobuf.ArmyPromote.army_promote_request.getDefaultInstance()) return this;
        if (other.hasArmyId()) {
          setArmyId(other.getArmyId());
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasArmyId()) {
          
          return false;
        }
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.ArmyPromote.army_promote_request parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.ArmyPromote.army_promote_request) e.getUnfinishedMessage();
          throw e;
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private int armyId_ ;
      /**
       * <code>required uint32 army_id = 1;</code>
       */
      public boolean hasArmyId() {
        return ((bitField0_ & 0x00000001) == 0x00000001);
      }
      /**
       * <code>required uint32 army_id = 1;</code>
       */
      public int getArmyId() {
        return armyId_;
      }
      /**
       * <code>required uint32 army_id = 1;</code>
       */
      public Builder setArmyId(int value) {
        bitField0_ |= 0x00000001;
        armyId_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 army_id = 1;</code>
       */
      public Builder clearArmyId() {
        bitField0_ = (bitField0_ & ~0x00000001);
        armyId_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:army_promote_request)
    }

    static {
      defaultInstance = new army_promote_request(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:army_promote_request)
  }

  public interface army_promoteOrBuilder extends
      // @@protoc_insertion_point(interface_extends:army_promote)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>required uint32 code = 1;</code>
     */
    boolean hasCode();
    /**
     * <code>required uint32 code = 1;</code>
     */
    int getCode();
  }
  /**
   * Protobuf type {@code army_promote}
   */
  public static final class army_promote extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:army_promote)
      army_promoteOrBuilder {
    // Use army_promote.newBuilder() to construct.
    private army_promote(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private army_promote(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final army_promote defaultInstance;
    public static army_promote getDefaultInstance() {
      return defaultInstance;
    }

    public army_promote getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private army_promote(
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
              code_ = input.readUInt32();
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
      return com.protobuf.ArmyPromote.internal_static_army_promote_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.ArmyPromote.internal_static_army_promote_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.ArmyPromote.army_promote.class, com.protobuf.ArmyPromote.army_promote.Builder.class);
    }

    public static com.google.protobuf.Parser<army_promote> PARSER =
        new com.google.protobuf.AbstractParser<army_promote>() {
      public army_promote parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new army_promote(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<army_promote> getParserForType() {
      return PARSER;
    }

    private int bitField0_;
    public static final int CODE_FIELD_NUMBER = 1;
    private int code_;
    /**
     * <code>required uint32 code = 1;</code>
     */
    public boolean hasCode() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required uint32 code = 1;</code>
     */
    public int getCode() {
      return code_;
    }

    private void initFields() {
      code_ = 0;
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      if (!hasCode()) {
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
        output.writeUInt32(1, code_);
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
          .computeUInt32Size(1, code_);
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

    public static com.protobuf.ArmyPromote.army_promote parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyPromote.army_promote parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyPromote.army_promote parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyPromote.army_promote parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyPromote.army_promote parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyPromote.army_promote parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyPromote.army_promote parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.ArmyPromote.army_promote parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyPromote.army_promote parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyPromote.army_promote parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.ArmyPromote.army_promote prototype) {
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
     * Protobuf type {@code army_promote}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:army_promote)
        com.protobuf.ArmyPromote.army_promoteOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.ArmyPromote.internal_static_army_promote_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.ArmyPromote.internal_static_army_promote_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.ArmyPromote.army_promote.class, com.protobuf.ArmyPromote.army_promote.Builder.class);
      }

      // Construct using com.protobuf.ArmyPromote.army_promote.newBuilder()
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
        code_ = 0;
        bitField0_ = (bitField0_ & ~0x00000001);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.ArmyPromote.internal_static_army_promote_descriptor;
      }

      public com.protobuf.ArmyPromote.army_promote getDefaultInstanceForType() {
        return com.protobuf.ArmyPromote.army_promote.getDefaultInstance();
      }

      public com.protobuf.ArmyPromote.army_promote build() {
        com.protobuf.ArmyPromote.army_promote result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.ArmyPromote.army_promote buildPartial() {
        com.protobuf.ArmyPromote.army_promote result = new com.protobuf.ArmyPromote.army_promote(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.code_ = code_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.ArmyPromote.army_promote) {
          return mergeFrom((com.protobuf.ArmyPromote.army_promote)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.ArmyPromote.army_promote other) {
        if (other == com.protobuf.ArmyPromote.army_promote.getDefaultInstance()) return this;
        if (other.hasCode()) {
          setCode(other.getCode());
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasCode()) {
          
          return false;
        }
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.ArmyPromote.army_promote parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.ArmyPromote.army_promote) e.getUnfinishedMessage();
          throw e;
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private int code_ ;
      /**
       * <code>required uint32 code = 1;</code>
       */
      public boolean hasCode() {
        return ((bitField0_ & 0x00000001) == 0x00000001);
      }
      /**
       * <code>required uint32 code = 1;</code>
       */
      public int getCode() {
        return code_;
      }
      /**
       * <code>required uint32 code = 1;</code>
       */
      public Builder setCode(int value) {
        bitField0_ |= 0x00000001;
        code_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 code = 1;</code>
       */
      public Builder clearCode() {
        bitField0_ = (bitField0_ & ~0x00000001);
        code_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:army_promote)
    }

    static {
      defaultInstance = new army_promote(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:army_promote)
  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_army_promote_request_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_army_promote_request_fieldAccessorTable;
  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_army_promote_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_army_promote_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\022army_promote.proto\"\'\n\024army_promote_req" +
      "uest\022\017\n\007army_id\030\001 \002(\r\"\034\n\014army_promote\022\014\n" +
      "\004code\030\001 \002(\rB\016\n\014com.protobuf"
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
    internal_static_army_promote_request_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_army_promote_request_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_army_promote_request_descriptor,
        new java.lang.String[] { "ArmyId", });
    internal_static_army_promote_descriptor =
      getDescriptor().getMessageTypes().get(1);
    internal_static_army_promote_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_army_promote_descriptor,
        new java.lang.String[] { "Code", });
  }

  // @@protoc_insertion_point(outer_class_scope)
}
