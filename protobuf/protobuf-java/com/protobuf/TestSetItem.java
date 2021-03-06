// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test_set_item.proto

package com.protobuf;

public final class TestSetItem {
  private TestSetItem() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
  }
  public interface test_set_item_requestOrBuilder extends
      // @@protoc_insertion_point(interface_extends:test_set_item_request)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>required uint32 item_type = 1;</code>
     */
    boolean hasItemType();
    /**
     * <code>required uint32 item_type = 1;</code>
     */
    int getItemType();

    /**
     * <code>required uint32 item_number = 2;</code>
     */
    boolean hasItemNumber();
    /**
     * <code>required uint32 item_number = 2;</code>
     */
    int getItemNumber();
  }
  /**
   * Protobuf type {@code test_set_item_request}
   */
  public static final class test_set_item_request extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:test_set_item_request)
      test_set_item_requestOrBuilder {
    // Use test_set_item_request.newBuilder() to construct.
    private test_set_item_request(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private test_set_item_request(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final test_set_item_request defaultInstance;
    public static test_set_item_request getDefaultInstance() {
      return defaultInstance;
    }

    public test_set_item_request getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private test_set_item_request(
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
              itemType_ = input.readUInt32();
              break;
            }
            case 16: {
              bitField0_ |= 0x00000002;
              itemNumber_ = input.readUInt32();
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
      return com.protobuf.TestSetItem.internal_static_test_set_item_request_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.TestSetItem.internal_static_test_set_item_request_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.TestSetItem.test_set_item_request.class, com.protobuf.TestSetItem.test_set_item_request.Builder.class);
    }

    public static com.google.protobuf.Parser<test_set_item_request> PARSER =
        new com.google.protobuf.AbstractParser<test_set_item_request>() {
      public test_set_item_request parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new test_set_item_request(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<test_set_item_request> getParserForType() {
      return PARSER;
    }

    private int bitField0_;
    public static final int ITEM_TYPE_FIELD_NUMBER = 1;
    private int itemType_;
    /**
     * <code>required uint32 item_type = 1;</code>
     */
    public boolean hasItemType() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required uint32 item_type = 1;</code>
     */
    public int getItemType() {
      return itemType_;
    }

    public static final int ITEM_NUMBER_FIELD_NUMBER = 2;
    private int itemNumber_;
    /**
     * <code>required uint32 item_number = 2;</code>
     */
    public boolean hasItemNumber() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required uint32 item_number = 2;</code>
     */
    public int getItemNumber() {
      return itemNumber_;
    }

    private void initFields() {
      itemType_ = 0;
      itemNumber_ = 0;
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      if (!hasItemType()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasItemNumber()) {
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
        output.writeUInt32(1, itemType_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeUInt32(2, itemNumber_);
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
          .computeUInt32Size(1, itemType_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(2, itemNumber_);
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

    public static com.protobuf.TestSetItem.test_set_item_request parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.TestSetItem.test_set_item_request parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.TestSetItem.test_set_item_request prototype) {
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
     * Protobuf type {@code test_set_item_request}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:test_set_item_request)
        com.protobuf.TestSetItem.test_set_item_requestOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.TestSetItem.internal_static_test_set_item_request_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.TestSetItem.internal_static_test_set_item_request_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.TestSetItem.test_set_item_request.class, com.protobuf.TestSetItem.test_set_item_request.Builder.class);
      }

      // Construct using com.protobuf.TestSetItem.test_set_item_request.newBuilder()
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
        itemType_ = 0;
        bitField0_ = (bitField0_ & ~0x00000001);
        itemNumber_ = 0;
        bitField0_ = (bitField0_ & ~0x00000002);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.TestSetItem.internal_static_test_set_item_request_descriptor;
      }

      public com.protobuf.TestSetItem.test_set_item_request getDefaultInstanceForType() {
        return com.protobuf.TestSetItem.test_set_item_request.getDefaultInstance();
      }

      public com.protobuf.TestSetItem.test_set_item_request build() {
        com.protobuf.TestSetItem.test_set_item_request result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.TestSetItem.test_set_item_request buildPartial() {
        com.protobuf.TestSetItem.test_set_item_request result = new com.protobuf.TestSetItem.test_set_item_request(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.itemType_ = itemType_;
        if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
          to_bitField0_ |= 0x00000002;
        }
        result.itemNumber_ = itemNumber_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.TestSetItem.test_set_item_request) {
          return mergeFrom((com.protobuf.TestSetItem.test_set_item_request)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.TestSetItem.test_set_item_request other) {
        if (other == com.protobuf.TestSetItem.test_set_item_request.getDefaultInstance()) return this;
        if (other.hasItemType()) {
          setItemType(other.getItemType());
        }
        if (other.hasItemNumber()) {
          setItemNumber(other.getItemNumber());
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasItemType()) {
          
          return false;
        }
        if (!hasItemNumber()) {
          
          return false;
        }
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.TestSetItem.test_set_item_request parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.TestSetItem.test_set_item_request) e.getUnfinishedMessage();
          throw e;
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private int itemType_ ;
      /**
       * <code>required uint32 item_type = 1;</code>
       */
      public boolean hasItemType() {
        return ((bitField0_ & 0x00000001) == 0x00000001);
      }
      /**
       * <code>required uint32 item_type = 1;</code>
       */
      public int getItemType() {
        return itemType_;
      }
      /**
       * <code>required uint32 item_type = 1;</code>
       */
      public Builder setItemType(int value) {
        bitField0_ |= 0x00000001;
        itemType_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 item_type = 1;</code>
       */
      public Builder clearItemType() {
        bitField0_ = (bitField0_ & ~0x00000001);
        itemType_ = 0;
        onChanged();
        return this;
      }

      private int itemNumber_ ;
      /**
       * <code>required uint32 item_number = 2;</code>
       */
      public boolean hasItemNumber() {
        return ((bitField0_ & 0x00000002) == 0x00000002);
      }
      /**
       * <code>required uint32 item_number = 2;</code>
       */
      public int getItemNumber() {
        return itemNumber_;
      }
      /**
       * <code>required uint32 item_number = 2;</code>
       */
      public Builder setItemNumber(int value) {
        bitField0_ |= 0x00000002;
        itemNumber_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 item_number = 2;</code>
       */
      public Builder clearItemNumber() {
        bitField0_ = (bitField0_ & ~0x00000002);
        itemNumber_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:test_set_item_request)
    }

    static {
      defaultInstance = new test_set_item_request(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:test_set_item_request)
  }

  public interface test_set_itemOrBuilder extends
      // @@protoc_insertion_point(interface_extends:test_set_item)
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
     * <code>required uint32 item_type = 2;</code>
     */
    boolean hasItemType();
    /**
     * <code>required uint32 item_type = 2;</code>
     */
    int getItemType();

    /**
     * <code>required uint32 item_number = 3;</code>
     */
    boolean hasItemNumber();
    /**
     * <code>required uint32 item_number = 3;</code>
     */
    int getItemNumber();
  }
  /**
   * Protobuf type {@code test_set_item}
   */
  public static final class test_set_item extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:test_set_item)
      test_set_itemOrBuilder {
    // Use test_set_item.newBuilder() to construct.
    private test_set_item(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private test_set_item(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final test_set_item defaultInstance;
    public static test_set_item getDefaultInstance() {
      return defaultInstance;
    }

    public test_set_item getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private test_set_item(
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
              itemType_ = input.readUInt32();
              break;
            }
            case 24: {
              bitField0_ |= 0x00000004;
              itemNumber_ = input.readUInt32();
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
      return com.protobuf.TestSetItem.internal_static_test_set_item_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.TestSetItem.internal_static_test_set_item_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.TestSetItem.test_set_item.class, com.protobuf.TestSetItem.test_set_item.Builder.class);
    }

    public static com.google.protobuf.Parser<test_set_item> PARSER =
        new com.google.protobuf.AbstractParser<test_set_item>() {
      public test_set_item parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new test_set_item(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<test_set_item> getParserForType() {
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

    public static final int ITEM_TYPE_FIELD_NUMBER = 2;
    private int itemType_;
    /**
     * <code>required uint32 item_type = 2;</code>
     */
    public boolean hasItemType() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required uint32 item_type = 2;</code>
     */
    public int getItemType() {
      return itemType_;
    }

    public static final int ITEM_NUMBER_FIELD_NUMBER = 3;
    private int itemNumber_;
    /**
     * <code>required uint32 item_number = 3;</code>
     */
    public boolean hasItemNumber() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>required uint32 item_number = 3;</code>
     */
    public int getItemNumber() {
      return itemNumber_;
    }

    private void initFields() {
      playerId_ = 0;
      itemType_ = 0;
      itemNumber_ = 0;
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
      if (!hasItemType()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasItemNumber()) {
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
        output.writeUInt32(2, itemType_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeUInt32(3, itemNumber_);
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
          .computeUInt32Size(2, itemType_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(3, itemNumber_);
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

    public static com.protobuf.TestSetItem.test_set_item parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.TestSetItem.test_set_item parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.TestSetItem.test_set_item parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.TestSetItem.test_set_item parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.TestSetItem.test_set_item parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.TestSetItem.test_set_item parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.TestSetItem.test_set_item parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.TestSetItem.test_set_item parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.TestSetItem.test_set_item parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.TestSetItem.test_set_item parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.TestSetItem.test_set_item prototype) {
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
     * Protobuf type {@code test_set_item}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:test_set_item)
        com.protobuf.TestSetItem.test_set_itemOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.TestSetItem.internal_static_test_set_item_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.TestSetItem.internal_static_test_set_item_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.TestSetItem.test_set_item.class, com.protobuf.TestSetItem.test_set_item.Builder.class);
      }

      // Construct using com.protobuf.TestSetItem.test_set_item.newBuilder()
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
        itemType_ = 0;
        bitField0_ = (bitField0_ & ~0x00000002);
        itemNumber_ = 0;
        bitField0_ = (bitField0_ & ~0x00000004);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.TestSetItem.internal_static_test_set_item_descriptor;
      }

      public com.protobuf.TestSetItem.test_set_item getDefaultInstanceForType() {
        return com.protobuf.TestSetItem.test_set_item.getDefaultInstance();
      }

      public com.protobuf.TestSetItem.test_set_item build() {
        com.protobuf.TestSetItem.test_set_item result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.TestSetItem.test_set_item buildPartial() {
        com.protobuf.TestSetItem.test_set_item result = new com.protobuf.TestSetItem.test_set_item(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.playerId_ = playerId_;
        if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
          to_bitField0_ |= 0x00000002;
        }
        result.itemType_ = itemType_;
        if (((from_bitField0_ & 0x00000004) == 0x00000004)) {
          to_bitField0_ |= 0x00000004;
        }
        result.itemNumber_ = itemNumber_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.TestSetItem.test_set_item) {
          return mergeFrom((com.protobuf.TestSetItem.test_set_item)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.TestSetItem.test_set_item other) {
        if (other == com.protobuf.TestSetItem.test_set_item.getDefaultInstance()) return this;
        if (other.hasPlayerId()) {
          setPlayerId(other.getPlayerId());
        }
        if (other.hasItemType()) {
          setItemType(other.getItemType());
        }
        if (other.hasItemNumber()) {
          setItemNumber(other.getItemNumber());
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasPlayerId()) {
          
          return false;
        }
        if (!hasItemType()) {
          
          return false;
        }
        if (!hasItemNumber()) {
          
          return false;
        }
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.TestSetItem.test_set_item parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.TestSetItem.test_set_item) e.getUnfinishedMessage();
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

      private int itemType_ ;
      /**
       * <code>required uint32 item_type = 2;</code>
       */
      public boolean hasItemType() {
        return ((bitField0_ & 0x00000002) == 0x00000002);
      }
      /**
       * <code>required uint32 item_type = 2;</code>
       */
      public int getItemType() {
        return itemType_;
      }
      /**
       * <code>required uint32 item_type = 2;</code>
       */
      public Builder setItemType(int value) {
        bitField0_ |= 0x00000002;
        itemType_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 item_type = 2;</code>
       */
      public Builder clearItemType() {
        bitField0_ = (bitField0_ & ~0x00000002);
        itemType_ = 0;
        onChanged();
        return this;
      }

      private int itemNumber_ ;
      /**
       * <code>required uint32 item_number = 3;</code>
       */
      public boolean hasItemNumber() {
        return ((bitField0_ & 0x00000004) == 0x00000004);
      }
      /**
       * <code>required uint32 item_number = 3;</code>
       */
      public int getItemNumber() {
        return itemNumber_;
      }
      /**
       * <code>required uint32 item_number = 3;</code>
       */
      public Builder setItemNumber(int value) {
        bitField0_ |= 0x00000004;
        itemNumber_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 item_number = 3;</code>
       */
      public Builder clearItemNumber() {
        bitField0_ = (bitField0_ & ~0x00000004);
        itemNumber_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:test_set_item)
    }

    static {
      defaultInstance = new test_set_item(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:test_set_item)
  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_test_set_item_request_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_test_set_item_request_fieldAccessorTable;
  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_test_set_item_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_test_set_item_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\023test_set_item.proto\"?\n\025test_set_item_r" +
      "equest\022\021\n\titem_type\030\001 \002(\r\022\023\n\013item_number" +
      "\030\002 \002(\r\"J\n\rtest_set_item\022\021\n\tplayer_id\030\001 \002" +
      "(\r\022\021\n\titem_type\030\002 \002(\r\022\023\n\013item_number\030\003 \002" +
      "(\rB\016\n\014com.protobuf"
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
    internal_static_test_set_item_request_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_test_set_item_request_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_test_set_item_request_descriptor,
        new java.lang.String[] { "ItemType", "ItemNumber", });
    internal_static_test_set_item_descriptor =
      getDescriptor().getMessageTypes().get(1);
    internal_static_test_set_item_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_test_set_item_descriptor,
        new java.lang.String[] { "PlayerId", "ItemType", "ItemNumber", });
  }

  // @@protoc_insertion_point(outer_class_scope)
}
