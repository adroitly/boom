// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: view_change.proto

package com.protobuf;

public final class ViewChange {
  private ViewChange() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
  }
  public interface view_change_requestOrBuilder extends
      // @@protoc_insertion_point(interface_extends:view_change_request)
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
     * <code>optional int32 x = 2;</code>
     */
    boolean hasX();
    /**
     * <code>optional int32 x = 2;</code>
     */
    int getX();

    /**
     * <code>optional int32 y = 3;</code>
     */
    boolean hasY();
    /**
     * <code>optional int32 y = 3;</code>
     */
    int getY();
  }
  /**
   * Protobuf type {@code view_change_request}
   */
  public static final class view_change_request extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:view_change_request)
      view_change_requestOrBuilder {
    // Use view_change_request.newBuilder() to construct.
    private view_change_request(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private view_change_request(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final view_change_request defaultInstance;
    public static view_change_request getDefaultInstance() {
      return defaultInstance;
    }

    public view_change_request getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private view_change_request(
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
              x_ = input.readInt32();
              break;
            }
            case 24: {
              bitField0_ |= 0x00000004;
              y_ = input.readInt32();
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
      return com.protobuf.ViewChange.internal_static_view_change_request_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.ViewChange.internal_static_view_change_request_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.ViewChange.view_change_request.class, com.protobuf.ViewChange.view_change_request.Builder.class);
    }

    public static com.google.protobuf.Parser<view_change_request> PARSER =
        new com.google.protobuf.AbstractParser<view_change_request>() {
      public view_change_request parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new view_change_request(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<view_change_request> getParserForType() {
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

    public static final int X_FIELD_NUMBER = 2;
    private int x_;
    /**
     * <code>optional int32 x = 2;</code>
     */
    public boolean hasX() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>optional int32 x = 2;</code>
     */
    public int getX() {
      return x_;
    }

    public static final int Y_FIELD_NUMBER = 3;
    private int y_;
    /**
     * <code>optional int32 y = 3;</code>
     */
    public boolean hasY() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>optional int32 y = 3;</code>
     */
    public int getY() {
      return y_;
    }

    private void initFields() {
      playerId_ = 0;
      x_ = 0;
      y_ = 0;
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
        output.writeInt32(2, x_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeInt32(3, y_);
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
          .computeInt32Size(2, x_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(3, y_);
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

    public static com.protobuf.ViewChange.view_change_request parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ViewChange.view_change_request parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ViewChange.view_change_request parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ViewChange.view_change_request parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ViewChange.view_change_request parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ViewChange.view_change_request parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.ViewChange.view_change_request parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.ViewChange.view_change_request parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.ViewChange.view_change_request parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ViewChange.view_change_request parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.ViewChange.view_change_request prototype) {
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
     * Protobuf type {@code view_change_request}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:view_change_request)
        com.protobuf.ViewChange.view_change_requestOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.ViewChange.internal_static_view_change_request_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.ViewChange.internal_static_view_change_request_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.ViewChange.view_change_request.class, com.protobuf.ViewChange.view_change_request.Builder.class);
      }

      // Construct using com.protobuf.ViewChange.view_change_request.newBuilder()
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
        x_ = 0;
        bitField0_ = (bitField0_ & ~0x00000002);
        y_ = 0;
        bitField0_ = (bitField0_ & ~0x00000004);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.ViewChange.internal_static_view_change_request_descriptor;
      }

      public com.protobuf.ViewChange.view_change_request getDefaultInstanceForType() {
        return com.protobuf.ViewChange.view_change_request.getDefaultInstance();
      }

      public com.protobuf.ViewChange.view_change_request build() {
        com.protobuf.ViewChange.view_change_request result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.ViewChange.view_change_request buildPartial() {
        com.protobuf.ViewChange.view_change_request result = new com.protobuf.ViewChange.view_change_request(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.playerId_ = playerId_;
        if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
          to_bitField0_ |= 0x00000002;
        }
        result.x_ = x_;
        if (((from_bitField0_ & 0x00000004) == 0x00000004)) {
          to_bitField0_ |= 0x00000004;
        }
        result.y_ = y_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.ViewChange.view_change_request) {
          return mergeFrom((com.protobuf.ViewChange.view_change_request)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.ViewChange.view_change_request other) {
        if (other == com.protobuf.ViewChange.view_change_request.getDefaultInstance()) return this;
        if (other.hasPlayerId()) {
          setPlayerId(other.getPlayerId());
        }
        if (other.hasX()) {
          setX(other.getX());
        }
        if (other.hasY()) {
          setY(other.getY());
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasPlayerId()) {
          
          return false;
        }
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.ViewChange.view_change_request parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.ViewChange.view_change_request) e.getUnfinishedMessage();
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

      private int x_ ;
      /**
       * <code>optional int32 x = 2;</code>
       */
      public boolean hasX() {
        return ((bitField0_ & 0x00000002) == 0x00000002);
      }
      /**
       * <code>optional int32 x = 2;</code>
       */
      public int getX() {
        return x_;
      }
      /**
       * <code>optional int32 x = 2;</code>
       */
      public Builder setX(int value) {
        bitField0_ |= 0x00000002;
        x_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional int32 x = 2;</code>
       */
      public Builder clearX() {
        bitField0_ = (bitField0_ & ~0x00000002);
        x_ = 0;
        onChanged();
        return this;
      }

      private int y_ ;
      /**
       * <code>optional int32 y = 3;</code>
       */
      public boolean hasY() {
        return ((bitField0_ & 0x00000004) == 0x00000004);
      }
      /**
       * <code>optional int32 y = 3;</code>
       */
      public int getY() {
        return y_;
      }
      /**
       * <code>optional int32 y = 3;</code>
       */
      public Builder setY(int value) {
        bitField0_ |= 0x00000004;
        y_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional int32 y = 3;</code>
       */
      public Builder clearY() {
        bitField0_ = (bitField0_ & ~0x00000004);
        y_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:view_change_request)
    }

    static {
      defaultInstance = new view_change_request(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:view_change_request)
  }

  public interface view_changeOrBuilder extends
      // @@protoc_insertion_point(interface_extends:view_change)
      com.google.protobuf.MessageOrBuilder {
  }
  /**
   * Protobuf type {@code view_change}
   */
  public static final class view_change extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:view_change)
      view_changeOrBuilder {
    // Use view_change.newBuilder() to construct.
    private view_change(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private view_change(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final view_change defaultInstance;
    public static view_change getDefaultInstance() {
      return defaultInstance;
    }

    public view_change getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private view_change(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      initFields();
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
      return com.protobuf.ViewChange.internal_static_view_change_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.ViewChange.internal_static_view_change_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.ViewChange.view_change.class, com.protobuf.ViewChange.view_change.Builder.class);
    }

    public static com.google.protobuf.Parser<view_change> PARSER =
        new com.google.protobuf.AbstractParser<view_change>() {
      public view_change parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new view_change(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<view_change> getParserForType() {
      return PARSER;
    }

    private void initFields() {
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      memoizedIsInitialized = 1;
      return true;
    }

    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      getSerializedSize();
      getUnknownFields().writeTo(output);
    }

    private int memoizedSerializedSize = -1;
    public int getSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
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

    public static com.protobuf.ViewChange.view_change parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ViewChange.view_change parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ViewChange.view_change parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ViewChange.view_change parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ViewChange.view_change parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ViewChange.view_change parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.ViewChange.view_change parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.ViewChange.view_change parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.ViewChange.view_change parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ViewChange.view_change parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.ViewChange.view_change prototype) {
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
     * Protobuf type {@code view_change}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:view_change)
        com.protobuf.ViewChange.view_changeOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.ViewChange.internal_static_view_change_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.ViewChange.internal_static_view_change_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.ViewChange.view_change.class, com.protobuf.ViewChange.view_change.Builder.class);
      }

      // Construct using com.protobuf.ViewChange.view_change.newBuilder()
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
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.ViewChange.internal_static_view_change_descriptor;
      }

      public com.protobuf.ViewChange.view_change getDefaultInstanceForType() {
        return com.protobuf.ViewChange.view_change.getDefaultInstance();
      }

      public com.protobuf.ViewChange.view_change build() {
        com.protobuf.ViewChange.view_change result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.ViewChange.view_change buildPartial() {
        com.protobuf.ViewChange.view_change result = new com.protobuf.ViewChange.view_change(this);
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.ViewChange.view_change) {
          return mergeFrom((com.protobuf.ViewChange.view_change)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.ViewChange.view_change other) {
        if (other == com.protobuf.ViewChange.view_change.getDefaultInstance()) return this;
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.ViewChange.view_change parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.ViewChange.view_change) e.getUnfinishedMessage();
          throw e;
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }

      // @@protoc_insertion_point(builder_scope:view_change)
    }

    static {
      defaultInstance = new view_change(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:view_change)
  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_view_change_request_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_view_change_request_fieldAccessorTable;
  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_view_change_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_view_change_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\021view_change.proto\">\n\023view_change_reque" +
      "st\022\021\n\tplayer_id\030\001 \002(\r\022\t\n\001x\030\002 \001(\005\022\t\n\001y\030\003 " +
      "\001(\005\"\r\n\013view_changeB\016\n\014com.protobuf"
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
    internal_static_view_change_request_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_view_change_request_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_view_change_request_descriptor,
        new java.lang.String[] { "PlayerId", "X", "Y", });
    internal_static_view_change_descriptor =
      getDescriptor().getMessageTypes().get(1);
    internal_static_view_change_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_view_change_descriptor,
        new java.lang.String[] { });
  }

  // @@protoc_insertion_point(outer_class_scope)
}
