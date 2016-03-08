// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: army_info.proto

package com.protobuf;

public final class ArmyInfo {
  private ArmyInfo() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
  }
  public interface army_infoOrBuilder extends
      // @@protoc_insertion_point(interface_extends:army_info)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>required uint32 army_state = 1;</code>
     *
     * <pre>
     *1 在城内, 2 在城外, 3 驻守
     * </pre>
     */
    boolean hasArmyState();
    /**
     * <code>required uint32 army_state = 1;</code>
     *
     * <pre>
     *1 在城内, 2 在城外, 3 驻守
     * </pre>
     */
    int getArmyState();

    /**
     * <code>required uint32 army_id = 2;</code>
     */
    boolean hasArmyId();
    /**
     * <code>required uint32 army_id = 2;</code>
     */
    int getArmyId();

    /**
     * <code>optional uint32 hero_id = 3;</code>
     */
    boolean hasHeroId();
    /**
     * <code>optional uint32 hero_id = 3;</code>
     */
    int getHeroId();

    /**
     * <code>optional uint32 soldier_type = 4;</code>
     */
    boolean hasSoldierType();
    /**
     * <code>optional uint32 soldier_type = 4;</code>
     */
    int getSoldierType();

    /**
     * <code>optional int32 from_x = 5;</code>
     */
    boolean hasFromX();
    /**
     * <code>optional int32 from_x = 5;</code>
     */
    int getFromX();

    /**
     * <code>optional int32 from_y = 6;</code>
     */
    boolean hasFromY();
    /**
     * <code>optional int32 from_y = 6;</code>
     */
    int getFromY();

    /**
     * <code>optional uint32 army_number = 7;</code>
     */
    boolean hasArmyNumber();
    /**
     * <code>optional uint32 army_number = 7;</code>
     */
    int getArmyNumber();

    /**
     * <code>optional uint32 food = 8;</code>
     */
    boolean hasFood();
    /**
     * <code>optional uint32 food = 8;</code>
     */
    int getFood();
  }
  /**
   * Protobuf type {@code army_info}
   */
  public static final class army_info extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:army_info)
      army_infoOrBuilder {
    // Use army_info.newBuilder() to construct.
    private army_info(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private army_info(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final army_info defaultInstance;
    public static army_info getDefaultInstance() {
      return defaultInstance;
    }

    public army_info getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private army_info(
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
              armyState_ = input.readUInt32();
              break;
            }
            case 16: {
              bitField0_ |= 0x00000002;
              armyId_ = input.readUInt32();
              break;
            }
            case 24: {
              bitField0_ |= 0x00000004;
              heroId_ = input.readUInt32();
              break;
            }
            case 32: {
              bitField0_ |= 0x00000008;
              soldierType_ = input.readUInt32();
              break;
            }
            case 40: {
              bitField0_ |= 0x00000010;
              fromX_ = input.readInt32();
              break;
            }
            case 48: {
              bitField0_ |= 0x00000020;
              fromY_ = input.readInt32();
              break;
            }
            case 56: {
              bitField0_ |= 0x00000040;
              armyNumber_ = input.readUInt32();
              break;
            }
            case 64: {
              bitField0_ |= 0x00000080;
              food_ = input.readUInt32();
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
      return com.protobuf.ArmyInfo.internal_static_army_info_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.ArmyInfo.internal_static_army_info_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.ArmyInfo.army_info.class, com.protobuf.ArmyInfo.army_info.Builder.class);
    }

    public static com.google.protobuf.Parser<army_info> PARSER =
        new com.google.protobuf.AbstractParser<army_info>() {
      public army_info parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new army_info(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<army_info> getParserForType() {
      return PARSER;
    }

    private int bitField0_;
    public static final int ARMY_STATE_FIELD_NUMBER = 1;
    private int armyState_;
    /**
     * <code>required uint32 army_state = 1;</code>
     *
     * <pre>
     *1 在城内, 2 在城外, 3 驻守
     * </pre>
     */
    public boolean hasArmyState() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required uint32 army_state = 1;</code>
     *
     * <pre>
     *1 在城内, 2 在城外, 3 驻守
     * </pre>
     */
    public int getArmyState() {
      return armyState_;
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

    public static final int HERO_ID_FIELD_NUMBER = 3;
    private int heroId_;
    /**
     * <code>optional uint32 hero_id = 3;</code>
     */
    public boolean hasHeroId() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>optional uint32 hero_id = 3;</code>
     */
    public int getHeroId() {
      return heroId_;
    }

    public static final int SOLDIER_TYPE_FIELD_NUMBER = 4;
    private int soldierType_;
    /**
     * <code>optional uint32 soldier_type = 4;</code>
     */
    public boolean hasSoldierType() {
      return ((bitField0_ & 0x00000008) == 0x00000008);
    }
    /**
     * <code>optional uint32 soldier_type = 4;</code>
     */
    public int getSoldierType() {
      return soldierType_;
    }

    public static final int FROM_X_FIELD_NUMBER = 5;
    private int fromX_;
    /**
     * <code>optional int32 from_x = 5;</code>
     */
    public boolean hasFromX() {
      return ((bitField0_ & 0x00000010) == 0x00000010);
    }
    /**
     * <code>optional int32 from_x = 5;</code>
     */
    public int getFromX() {
      return fromX_;
    }

    public static final int FROM_Y_FIELD_NUMBER = 6;
    private int fromY_;
    /**
     * <code>optional int32 from_y = 6;</code>
     */
    public boolean hasFromY() {
      return ((bitField0_ & 0x00000020) == 0x00000020);
    }
    /**
     * <code>optional int32 from_y = 6;</code>
     */
    public int getFromY() {
      return fromY_;
    }

    public static final int ARMY_NUMBER_FIELD_NUMBER = 7;
    private int armyNumber_;
    /**
     * <code>optional uint32 army_number = 7;</code>
     */
    public boolean hasArmyNumber() {
      return ((bitField0_ & 0x00000040) == 0x00000040);
    }
    /**
     * <code>optional uint32 army_number = 7;</code>
     */
    public int getArmyNumber() {
      return armyNumber_;
    }

    public static final int FOOD_FIELD_NUMBER = 8;
    private int food_;
    /**
     * <code>optional uint32 food = 8;</code>
     */
    public boolean hasFood() {
      return ((bitField0_ & 0x00000080) == 0x00000080);
    }
    /**
     * <code>optional uint32 food = 8;</code>
     */
    public int getFood() {
      return food_;
    }

    private void initFields() {
      armyState_ = 0;
      armyId_ = 0;
      heroId_ = 0;
      soldierType_ = 0;
      fromX_ = 0;
      fromY_ = 0;
      armyNumber_ = 0;
      food_ = 0;
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      if (!hasArmyState()) {
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
        output.writeUInt32(1, armyState_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeUInt32(2, armyId_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeUInt32(3, heroId_);
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        output.writeUInt32(4, soldierType_);
      }
      if (((bitField0_ & 0x00000010) == 0x00000010)) {
        output.writeInt32(5, fromX_);
      }
      if (((bitField0_ & 0x00000020) == 0x00000020)) {
        output.writeInt32(6, fromY_);
      }
      if (((bitField0_ & 0x00000040) == 0x00000040)) {
        output.writeUInt32(7, armyNumber_);
      }
      if (((bitField0_ & 0x00000080) == 0x00000080)) {
        output.writeUInt32(8, food_);
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
          .computeUInt32Size(1, armyState_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(2, armyId_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(3, heroId_);
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(4, soldierType_);
      }
      if (((bitField0_ & 0x00000010) == 0x00000010)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(5, fromX_);
      }
      if (((bitField0_ & 0x00000020) == 0x00000020)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(6, fromY_);
      }
      if (((bitField0_ & 0x00000040) == 0x00000040)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(7, armyNumber_);
      }
      if (((bitField0_ & 0x00000080) == 0x00000080)) {
        size += com.google.protobuf.CodedOutputStream
          .computeUInt32Size(8, food_);
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

    public static com.protobuf.ArmyInfo.army_info parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyInfo.army_info parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyInfo.army_info parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.ArmyInfo.army_info parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.ArmyInfo.army_info parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyInfo.army_info parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyInfo.army_info parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.ArmyInfo.army_info parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.ArmyInfo.army_info parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.ArmyInfo.army_info parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.ArmyInfo.army_info prototype) {
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
     * Protobuf type {@code army_info}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:army_info)
        com.protobuf.ArmyInfo.army_infoOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.ArmyInfo.internal_static_army_info_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.ArmyInfo.internal_static_army_info_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.ArmyInfo.army_info.class, com.protobuf.ArmyInfo.army_info.Builder.class);
      }

      // Construct using com.protobuf.ArmyInfo.army_info.newBuilder()
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
        armyState_ = 0;
        bitField0_ = (bitField0_ & ~0x00000001);
        armyId_ = 0;
        bitField0_ = (bitField0_ & ~0x00000002);
        heroId_ = 0;
        bitField0_ = (bitField0_ & ~0x00000004);
        soldierType_ = 0;
        bitField0_ = (bitField0_ & ~0x00000008);
        fromX_ = 0;
        bitField0_ = (bitField0_ & ~0x00000010);
        fromY_ = 0;
        bitField0_ = (bitField0_ & ~0x00000020);
        armyNumber_ = 0;
        bitField0_ = (bitField0_ & ~0x00000040);
        food_ = 0;
        bitField0_ = (bitField0_ & ~0x00000080);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.ArmyInfo.internal_static_army_info_descriptor;
      }

      public com.protobuf.ArmyInfo.army_info getDefaultInstanceForType() {
        return com.protobuf.ArmyInfo.army_info.getDefaultInstance();
      }

      public com.protobuf.ArmyInfo.army_info build() {
        com.protobuf.ArmyInfo.army_info result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.ArmyInfo.army_info buildPartial() {
        com.protobuf.ArmyInfo.army_info result = new com.protobuf.ArmyInfo.army_info(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.armyState_ = armyState_;
        if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
          to_bitField0_ |= 0x00000002;
        }
        result.armyId_ = armyId_;
        if (((from_bitField0_ & 0x00000004) == 0x00000004)) {
          to_bitField0_ |= 0x00000004;
        }
        result.heroId_ = heroId_;
        if (((from_bitField0_ & 0x00000008) == 0x00000008)) {
          to_bitField0_ |= 0x00000008;
        }
        result.soldierType_ = soldierType_;
        if (((from_bitField0_ & 0x00000010) == 0x00000010)) {
          to_bitField0_ |= 0x00000010;
        }
        result.fromX_ = fromX_;
        if (((from_bitField0_ & 0x00000020) == 0x00000020)) {
          to_bitField0_ |= 0x00000020;
        }
        result.fromY_ = fromY_;
        if (((from_bitField0_ & 0x00000040) == 0x00000040)) {
          to_bitField0_ |= 0x00000040;
        }
        result.armyNumber_ = armyNumber_;
        if (((from_bitField0_ & 0x00000080) == 0x00000080)) {
          to_bitField0_ |= 0x00000080;
        }
        result.food_ = food_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.ArmyInfo.army_info) {
          return mergeFrom((com.protobuf.ArmyInfo.army_info)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.ArmyInfo.army_info other) {
        if (other == com.protobuf.ArmyInfo.army_info.getDefaultInstance()) return this;
        if (other.hasArmyState()) {
          setArmyState(other.getArmyState());
        }
        if (other.hasArmyId()) {
          setArmyId(other.getArmyId());
        }
        if (other.hasHeroId()) {
          setHeroId(other.getHeroId());
        }
        if (other.hasSoldierType()) {
          setSoldierType(other.getSoldierType());
        }
        if (other.hasFromX()) {
          setFromX(other.getFromX());
        }
        if (other.hasFromY()) {
          setFromY(other.getFromY());
        }
        if (other.hasArmyNumber()) {
          setArmyNumber(other.getArmyNumber());
        }
        if (other.hasFood()) {
          setFood(other.getFood());
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasArmyState()) {
          
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
        com.protobuf.ArmyInfo.army_info parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.ArmyInfo.army_info) e.getUnfinishedMessage();
          throw e;
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private int armyState_ ;
      /**
       * <code>required uint32 army_state = 1;</code>
       *
       * <pre>
       *1 在城内, 2 在城外, 3 驻守
       * </pre>
       */
      public boolean hasArmyState() {
        return ((bitField0_ & 0x00000001) == 0x00000001);
      }
      /**
       * <code>required uint32 army_state = 1;</code>
       *
       * <pre>
       *1 在城内, 2 在城外, 3 驻守
       * </pre>
       */
      public int getArmyState() {
        return armyState_;
      }
      /**
       * <code>required uint32 army_state = 1;</code>
       *
       * <pre>
       *1 在城内, 2 在城外, 3 驻守
       * </pre>
       */
      public Builder setArmyState(int value) {
        bitField0_ |= 0x00000001;
        armyState_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required uint32 army_state = 1;</code>
       *
       * <pre>
       *1 在城内, 2 在城外, 3 驻守
       * </pre>
       */
      public Builder clearArmyState() {
        bitField0_ = (bitField0_ & ~0x00000001);
        armyState_ = 0;
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

      private int heroId_ ;
      /**
       * <code>optional uint32 hero_id = 3;</code>
       */
      public boolean hasHeroId() {
        return ((bitField0_ & 0x00000004) == 0x00000004);
      }
      /**
       * <code>optional uint32 hero_id = 3;</code>
       */
      public int getHeroId() {
        return heroId_;
      }
      /**
       * <code>optional uint32 hero_id = 3;</code>
       */
      public Builder setHeroId(int value) {
        bitField0_ |= 0x00000004;
        heroId_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional uint32 hero_id = 3;</code>
       */
      public Builder clearHeroId() {
        bitField0_ = (bitField0_ & ~0x00000004);
        heroId_ = 0;
        onChanged();
        return this;
      }

      private int soldierType_ ;
      /**
       * <code>optional uint32 soldier_type = 4;</code>
       */
      public boolean hasSoldierType() {
        return ((bitField0_ & 0x00000008) == 0x00000008);
      }
      /**
       * <code>optional uint32 soldier_type = 4;</code>
       */
      public int getSoldierType() {
        return soldierType_;
      }
      /**
       * <code>optional uint32 soldier_type = 4;</code>
       */
      public Builder setSoldierType(int value) {
        bitField0_ |= 0x00000008;
        soldierType_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional uint32 soldier_type = 4;</code>
       */
      public Builder clearSoldierType() {
        bitField0_ = (bitField0_ & ~0x00000008);
        soldierType_ = 0;
        onChanged();
        return this;
      }

      private int fromX_ ;
      /**
       * <code>optional int32 from_x = 5;</code>
       */
      public boolean hasFromX() {
        return ((bitField0_ & 0x00000010) == 0x00000010);
      }
      /**
       * <code>optional int32 from_x = 5;</code>
       */
      public int getFromX() {
        return fromX_;
      }
      /**
       * <code>optional int32 from_x = 5;</code>
       */
      public Builder setFromX(int value) {
        bitField0_ |= 0x00000010;
        fromX_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional int32 from_x = 5;</code>
       */
      public Builder clearFromX() {
        bitField0_ = (bitField0_ & ~0x00000010);
        fromX_ = 0;
        onChanged();
        return this;
      }

      private int fromY_ ;
      /**
       * <code>optional int32 from_y = 6;</code>
       */
      public boolean hasFromY() {
        return ((bitField0_ & 0x00000020) == 0x00000020);
      }
      /**
       * <code>optional int32 from_y = 6;</code>
       */
      public int getFromY() {
        return fromY_;
      }
      /**
       * <code>optional int32 from_y = 6;</code>
       */
      public Builder setFromY(int value) {
        bitField0_ |= 0x00000020;
        fromY_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional int32 from_y = 6;</code>
       */
      public Builder clearFromY() {
        bitField0_ = (bitField0_ & ~0x00000020);
        fromY_ = 0;
        onChanged();
        return this;
      }

      private int armyNumber_ ;
      /**
       * <code>optional uint32 army_number = 7;</code>
       */
      public boolean hasArmyNumber() {
        return ((bitField0_ & 0x00000040) == 0x00000040);
      }
      /**
       * <code>optional uint32 army_number = 7;</code>
       */
      public int getArmyNumber() {
        return armyNumber_;
      }
      /**
       * <code>optional uint32 army_number = 7;</code>
       */
      public Builder setArmyNumber(int value) {
        bitField0_ |= 0x00000040;
        armyNumber_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional uint32 army_number = 7;</code>
       */
      public Builder clearArmyNumber() {
        bitField0_ = (bitField0_ & ~0x00000040);
        armyNumber_ = 0;
        onChanged();
        return this;
      }

      private int food_ ;
      /**
       * <code>optional uint32 food = 8;</code>
       */
      public boolean hasFood() {
        return ((bitField0_ & 0x00000080) == 0x00000080);
      }
      /**
       * <code>optional uint32 food = 8;</code>
       */
      public int getFood() {
        return food_;
      }
      /**
       * <code>optional uint32 food = 8;</code>
       */
      public Builder setFood(int value) {
        bitField0_ |= 0x00000080;
        food_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>optional uint32 food = 8;</code>
       */
      public Builder clearFood() {
        bitField0_ = (bitField0_ & ~0x00000080);
        food_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:army_info)
    }

    static {
      defaultInstance = new army_info(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:army_info)
  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_army_info_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_army_info_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\017army_info.proto\"\232\001\n\tarmy_info\022\022\n\narmy_" +
      "state\030\001 \002(\r\022\017\n\007army_id\030\002 \002(\r\022\017\n\007hero_id\030" +
      "\003 \001(\r\022\024\n\014soldier_type\030\004 \001(\r\022\016\n\006from_x\030\005 " +
      "\001(\005\022\016\n\006from_y\030\006 \001(\005\022\023\n\013army_number\030\007 \001(\r" +
      "\022\014\n\004food\030\010 \001(\rB\016\n\014com.protobuf"
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
    internal_static_army_info_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_army_info_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_army_info_descriptor,
        new java.lang.String[] { "ArmyState", "ArmyId", "HeroId", "SoldierType", "FromX", "FromY", "ArmyNumber", "Food", });
  }

  // @@protoc_insertion_point(outer_class_scope)
}