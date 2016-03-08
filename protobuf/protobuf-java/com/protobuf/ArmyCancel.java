// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: army_cancel.proto

package com.protobuf;

public final class ArmyCancel {
  private ArmyCancel() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
  }
  public interface army_cancel_requestOrBuilder extends
      // @@protoc_insertion_point(interface_extends:army_cancel_request)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>required uint32 player_id = 1;</code>
     */
    boolean hasPlayerId();
    /**
     * <code>required uint32 player_id = 1;</code>
     */
    int getPlayerId();

    /**
     * <code>required uint32 army_id = 2;</code>
     */
    boolean hasArmyId();
    /**
     * <code>required uint32 army_id = 2;</code>
     */
    int getArmyId();
  }
  /**
   * Protobuf type {@code army_cancel_request}
   */
  public static final class army_cancel_request extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:army_cancel_request)
      army_cancel_requestOrBuilder {
    // Use army_cancel_request.newBuilder() to construct.
    private army_cancel_request(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private army_cancel_request(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final army_cancel_request defaultInstance;
    public static army_cancel_request getDefaultInstance() {
      return defaultInstance;
    }

    public army_cancel_request getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private army_cancel_request(
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
              playerId_ = input.readUInt32();
              break;
            }
            case 16: {
              bitField0_ |= 0x00000002;
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
      return com.protobuf.ArmyCancel.internal_static_army_cancel_request_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.ArmyCancel.internal_static_army_cancel_request_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.ArmyCancel.army_cancel_request.class, com.protobuf.ArmyCancel.army_cancel_request.Builder.class);
    }

    public static com.google.protobuf.Parser<army_cancel_request> PARSER =
        new com.google.protobuf.AbstractParser<army_cancel_request>() {
      public army_cancel_request parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new army_cancel_request(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<army_cancel_request> getParserForType() {
      return PARSER;
    }

    private int bitField0_;
    public static final int PLAYER_ID_FIELD_NUMBER = 1;
    private int playerId_;
    /**
     * <code>required uint32 player_id = 1;</code>
     */
    public boolean hasPlayerId() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required uint32 player_id = 1;</code>
     */
    public int getPlayerId() {
      return playerId_;
    }

    public static final int ARMY_ID_FIELD_NUMBER = 2;
    private int armyId_;
    /**
     * <code>required uint32 army_id = 2;</code>
     */
    public boolean hasArmyId() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required uint32 army_id = 2;</code>
     */
    public int getArmyId() {
      return armyId_;
    }

    private void initFields() {
      playerId_ = 0;
      armyId_ = 0;
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      if (!hasPlayerId()) {
        memoizedIsInitialized = 0;
        return false;
      }
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
        output.writeUInt32(1, playerId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeUInt32(2, armyId_);
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
          .computeUInt32Size(1, playerId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(2, armyId_);
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

    public static com.protobuf.ArmyCancel.army_cancel_request parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyCancel.army_cancel_request parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.ArmyCancel.army_cancel_request prototype) {
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
     * Protobuf type {@code army_cancel_request}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:army_cancel_request)
        com.protobuf.ArmyCancel.army_cancel_requestOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.ArmyCancel.internal_static_army_cancel_request_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.ArmyCancel.internal_static_army_cancel_request_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.ArmyCancel.army_cancel_request.class, com.protobuf.ArmyCancel.army_cancel_request.Builder.class);
      }

      // Construct using com.protobuf.ArmyCancel.army_cancel_request.newBuilder()
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
        playerId_ = 0;
        bitField0_ = (bitField0_ & ~0x00000001);
        armyId_ = 0;
        bitField0_ = (bitField0_ & ~0x00000002);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.ArmyCancel.internal_static_army_cancel_request_descriptor;
      }

      public com.protobuf.ArmyCancel.army_cancel_request getDefaultInstanceForType() {
        return com.protobuf.ArmyCancel.army_cancel_request.getDefaultInstance();
      }

      public com.protobuf.ArmyCancel.army_cancel_request build() {
        com.protobuf.ArmyCancel.army_cancel_request result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.ArmyCancel.army_cancel_request buildPartial() {
        com.protobuf.ArmyCancel.army_cancel_request result = new com.protobuf.ArmyCancel.army_cancel_request(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.playerId_ = playerId_;
        if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
          to_bitField0_ |= 0x00000002;
        }
        result.armyId_ = armyId_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.ArmyCancel.army_cancel_request) {
          return mergeFrom((com.protobuf.ArmyCancel.army_cancel_request)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.ArmyCancel.army_cancel_request other) {
        if (other == com.protobuf.ArmyCancel.army_cancel_request.getDefaultInstance()) return this;
        if (other.hasPlayerId()) {
          setPlayerId(other.getPlayerId());
        }
        if (other.hasArmyId()) {
          setArmyId(other.getArmyId());
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasPlayerId()) {
          
          return false;
        }
        if (!hasArmyId()) {
          
          return false;
        }
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.ArmyCancel.army_cancel_request parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.ArmyCancel.army_cancel_request) e.getUnfinishedMessage();
          throw e;
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private int playerId_ ;
      /**
       * <code>required uint32 player_id = 1;</code>
       */
      public boolean hasPlayerId() {
        return ((bitField0_ & 0x00000001) == 0x00000001);
      }
      /**
       * <code>required uint32 player_id = 1;</code>
       */
      public int getPlayerId() {
        return playerId_;
      }
      /**
       * <code>required uint32 player_id = 1;</code>
       */
      public Builder setPlayerId(int value) {
        bitField0_ |= 0x00000001;
        playerId_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 player_id = 1;</code>
       */
      public Builder clearPlayerId() {
        bitField0_ = (bitField0_ & ~0x00000001);
        playerId_ = 0;
        onChanged();
        return this;
      }

      private int armyId_ ;
      /**
       * <code>required uint32 army_id = 2;</code>
       */
      public boolean hasArmyId() {
        return ((bitField0_ & 0x00000002) == 0x00000002);
      }
      /**
       * <code>required uint32 army_id = 2;</code>
       */
      public int getArmyId() {
        return armyId_;
      }
      /**
       * <code>required uint32 army_id = 2;</code>
       */
      public Builder setArmyId(int value) {
        bitField0_ |= 0x00000002;
        armyId_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 army_id = 2;</code>
       */
      public Builder clearArmyId() {
        bitField0_ = (bitField0_ & ~0x00000002);
        armyId_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:army_cancel_request)
    }

    static {
      defaultInstance = new army_cancel_request(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:army_cancel_request)
  }

  public interface army_cancelOrBuilder extends
      // @@protoc_insertion_point(interface_extends:army_cancel)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>required uint32 code = 1;</code>
     */
    boolean hasCode();
    /**
     * <code>required uint32 code = 1;</code>
     */
    int getCode();

    /**
     * <code>optional uint32 player_id = 2;</code>
     */
    boolean hasPlayerId();
    /**
     * <code>optional uint32 player_id = 2;</code>
     */
    int getPlayerId();

    /**
     * <code>optional uint32 army_id = 3;</code>
     */
    boolean hasArmyId();
    /**
     * <code>optional uint32 army_id = 3;</code>
     */
    int getArmyId();
  }
  /**
   * Protobuf type {@code army_cancel}
   */
  public static final class army_cancel extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:army_cancel)
      army_cancelOrBuilder {
    // Use army_cancel.newBuilder() to construct.
    private army_cancel(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private army_cancel(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final army_cancel defaultInstance;
    public static army_cancel getDefaultInstance() {
      return defaultInstance;
    }

    public army_cancel getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private army_cancel(
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
            case 16: {
              bitField0_ |= 0x00000002;
              playerId_ = input.readUInt32();
              break;
            }
            case 24: {
              bitField0_ |= 0x00000004;
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
      return com.protobuf.ArmyCancel.internal_static_army_cancel_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.ArmyCancel.internal_static_army_cancel_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.ArmyCancel.army_cancel.class, com.protobuf.ArmyCancel.army_cancel.Builder.class);
    }

    public static com.google.protobuf.Parser<army_cancel> PARSER =
        new com.google.protobuf.AbstractParser<army_cancel>() {
      public army_cancel parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new army_cancel(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<army_cancel> getParserForType() {
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

    public static final int PLAYER_ID_FIELD_NUMBER = 2;
    private int playerId_;
    /**
     * <code>optional uint32 player_id = 2;</code>
     */
    public boolean hasPlayerId() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>optional uint32 player_id = 2;</code>
     */
    public int getPlayerId() {
      return playerId_;
    }

    public static final int ARMY_ID_FIELD_NUMBER = 3;
    private int armyId_;
    /**
     * <code>optional uint32 army_id = 3;</code>
     */
    public boolean hasArmyId() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>optional uint32 army_id = 3;</code>
     */
    public int getArmyId() {
      return armyId_;
    }

    private void initFields() {
      code_ = 0;
      playerId_ = 0;
      armyId_ = 0;
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
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeUInt32(2, playerId_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeUInt32(3, armyId_);
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
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(2, playerId_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(3, armyId_);
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

    public static com.protobuf.ArmyCancel.army_cancel parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyCancel.army_cancel parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.ArmyCancel.army_cancel prototype) {
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
     * Protobuf type {@code army_cancel}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:army_cancel)
        com.protobuf.ArmyCancel.army_cancelOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.ArmyCancel.internal_static_army_cancel_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.ArmyCancel.internal_static_army_cancel_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.ArmyCancel.army_cancel.class, com.protobuf.ArmyCancel.army_cancel.Builder.class);
      }

      // Construct using com.protobuf.ArmyCancel.army_cancel.newBuilder()
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
        playerId_ = 0;
        bitField0_ = (bitField0_ & ~0x00000002);
        armyId_ = 0;
        bitField0_ = (bitField0_ & ~0x00000004);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.ArmyCancel.internal_static_army_cancel_descriptor;
      }

      public com.protobuf.ArmyCancel.army_cancel getDefaultInstanceForType() {
        return com.protobuf.ArmyCancel.army_cancel.getDefaultInstance();
      }

      public com.protobuf.ArmyCancel.army_cancel build() {
        com.protobuf.ArmyCancel.army_cancel result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.ArmyCancel.army_cancel buildPartial() {
        com.protobuf.ArmyCancel.army_cancel result = new com.protobuf.ArmyCancel.army_cancel(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.code_ = code_;
        if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
          to_bitField0_ |= 0x00000002;
        }
        result.playerId_ = playerId_;
        if (((from_bitField0_ & 0x00000004) == 0x00000004)) {
          to_bitField0_ |= 0x00000004;
        }
        result.armyId_ = armyId_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.ArmyCancel.army_cancel) {
          return mergeFrom((com.protobuf.ArmyCancel.army_cancel)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.ArmyCancel.army_cancel other) {
        if (other == com.protobuf.ArmyCancel.army_cancel.getDefaultInstance()) return this;
        if (other.hasCode()) {
          setCode(other.getCode());
        }
        if (other.hasPlayerId()) {
          setPlayerId(other.getPlayerId());
        }
        if (other.hasArmyId()) {
          setArmyId(other.getArmyId());
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
        com.protobuf.ArmyCancel.army_cancel parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.ArmyCancel.army_cancel) e.getUnfinishedMessage();
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

      private int playerId_ ;
      /**
       * <code>optional uint32 player_id = 2;</code>
       */
      public boolean hasPlayerId() {
        return ((bitField0_ & 0x00000002) == 0x00000002);
      }
      /**
       * <code>optional uint32 player_id = 2;</code>
       */
      public int getPlayerId() {
        return playerId_;
      }
      /**
       * <code>optional uint32 player_id = 2;</code>
       */
      public Builder setPlayerId(int value) {
        bitField0_ |= 0x00000002;
        playerId_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional uint32 player_id = 2;</code>
       */
      public Builder clearPlayerId() {
        bitField0_ = (bitField0_ & ~0x00000002);
        playerId_ = 0;
        onChanged();
        return this;
      }

      private int armyId_ ;
      /**
       * <code>optional uint32 army_id = 3;</code>
       */
      public boolean hasArmyId() {
        return ((bitField0_ & 0x00000004) == 0x00000004);
      }
      /**
       * <code>optional uint32 army_id = 3;</code>
       */
      public int getArmyId() {
        return armyId_;
      }
      /**
       * <code>optional uint32 army_id = 3;</code>
       */
      public Builder setArmyId(int value) {
        bitField0_ |= 0x00000004;
        armyId_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional uint32 army_id = 3;</code>
       */
      public Builder clearArmyId() {
        bitField0_ = (bitField0_ & ~0x00000004);
        armyId_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:army_cancel)
    }

    static {
      defaultInstance = new army_cancel(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:army_cancel)
  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_army_cancel_request_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_army_cancel_request_fieldAccessorTable;
  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_army_cancel_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_army_cancel_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\021army_cancel.proto\"9\n\023army_cancel_reque" +
      "st\022\021\n\tplayer_id\030\001 \002(\r\022\017\n\007army_id\030\002 \002(\r\"?" +
      "\n\013army_cancel\022\014\n\004code\030\001 \002(\r\022\021\n\tplayer_id" +
      "\030\002 \001(\r\022\017\n\007army_id\030\003 \001(\rB\016\n\014com.protobuf"
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
    internal_static_army_cancel_request_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_army_cancel_request_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_army_cancel_request_descriptor,
        new java.lang.String[] { "PlayerId", "ArmyId", });
    internal_static_army_cancel_descriptor =
      getDescriptor().getMessageTypes().get(1);
    internal_static_army_cancel_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_army_cancel_descriptor,
        new java.lang.String[] { "Code", "PlayerId", "ArmyId", });
  }

  // @@protoc_insertion_point(outer_class_scope)
}