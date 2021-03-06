// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: guild_member.proto

package com.protobuf;

public final class GuildMember {
  private GuildMember() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
  }
  public interface guild_memberOrBuilder extends
      // @@protoc_insertion_point(interface_extends:guild_member)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>required int32 memerId = 1;</code>
     *
     * <pre>
     *成员id
     * </pre>
     */
    boolean hasMemerId();
    /**
     * <code>required int32 memerId = 1;</code>
     *
     * <pre>
     *成员id
     * </pre>
     */
    int getMemerId();

    /**
     * <code>required int32 title = 2;</code>
     *
     * <pre>
     *成员封号
     * </pre>
     */
    boolean hasTitle();
    /**
     * <code>required int32 title = 2;</code>
     *
     * <pre>
     *成员封号
     * </pre>
     */
    int getTitle();

    /**
     * <code>required int32 contributeNum = 3;</code>
     *
     * <pre>
     *个人累计贡献
     * </pre>
     */
    boolean hasContributeNum();
    /**
     * <code>required int32 contributeNum = 3;</code>
     *
     * <pre>
     *个人累计贡献
     * </pre>
     */
    int getContributeNum();

    /**
     * <code>required int32 currContributeNum = 4;</code>
     *
     * <pre>
     *个人当前剩余贡献
     * </pre>
     */
    boolean hasCurrContributeNum();
    /**
     * <code>required int32 currContributeNum = 4;</code>
     *
     * <pre>
     *个人当前剩余贡献
     * </pre>
     */
    int getCurrContributeNum();

    /**
     * <code>required int32 oldCbNum = 5;</code>
     *
     * <pre>
     *个人昨日捐献
     * </pre>
     */
    boolean hasOldCbNum();
    /**
     * <code>required int32 oldCbNum = 5;</code>
     *
     * <pre>
     *个人昨日捐献
     * </pre>
     */
    int getOldCbNum();

    /**
     * <code>required int32 newCbNum = 6;</code>
     *
     * <pre>
     *个人今日零点截止到当前时间时间的 捐献总数量	
     * </pre>
     */
    boolean hasNewCbNum();
    /**
     * <code>required int32 newCbNum = 6;</code>
     *
     * <pre>
     *个人今日零点截止到当前时间时间的 捐献总数量	
     * </pre>
     */
    int getNewCbNum();
  }
  /**
   * Protobuf type {@code guild_member}
   *
   * <pre>
   * 势力成员信息
   * </pre>
   */
  public static final class guild_member extends
      com.google.protobuf.GeneratedMessage implements
      // @@protoc_insertion_point(message_implements:guild_member)
      guild_memberOrBuilder {
    // Use guild_member.newBuilder() to construct.
    private guild_member(com.google.protobuf.GeneratedMessage.Builder<?> builder) {
      super(builder);
      this.unknownFields = builder.getUnknownFields();
    }
    private guild_member(boolean noInit) { this.unknownFields = com.google.protobuf.UnknownFieldSet.getDefaultInstance(); }

    private static final guild_member defaultInstance;
    public static guild_member getDefaultInstance() {
      return defaultInstance;
    }

    public guild_member getDefaultInstanceForType() {
      return defaultInstance;
    }

    private final com.google.protobuf.UnknownFieldSet unknownFields;
    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
        getUnknownFields() {
      return this.unknownFields;
    }
    private guild_member(
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
              memerId_ = input.readInt32();
              break;
            }
            case 16: {
              bitField0_ |= 0x00000002;
              title_ = input.readInt32();
              break;
            }
            case 24: {
              bitField0_ |= 0x00000004;
              contributeNum_ = input.readInt32();
              break;
            }
            case 32: {
              bitField0_ |= 0x00000008;
              currContributeNum_ = input.readInt32();
              break;
            }
            case 40: {
              bitField0_ |= 0x00000010;
              oldCbNum_ = input.readInt32();
              break;
            }
            case 48: {
              bitField0_ |= 0x00000020;
              newCbNum_ = input.readInt32();
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
      return com.protobuf.GuildMember.internal_static_guild_member_descriptor;
    }

    protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return com.protobuf.GuildMember.internal_static_guild_member_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              com.protobuf.GuildMember.guild_member.class, com.protobuf.GuildMember.guild_member.Builder.class);
    }

    public static com.google.protobuf.Parser<guild_member> PARSER =
        new com.google.protobuf.AbstractParser<guild_member>() {
      public guild_member parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        return new guild_member(input, extensionRegistry);
      }
    };

    @java.lang.Override
    public com.google.protobuf.Parser<guild_member> getParserForType() {
      return PARSER;
    }

    private int bitField0_;
    public static final int MEMERID_FIELD_NUMBER = 1;
    private int memerId_;
    /**
     * <code>required int32 memerId = 1;</code>
     *
     * <pre>
     *成员id
     * </pre>
     */
    public boolean hasMemerId() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required int32 memerId = 1;</code>
     *
     * <pre>
     *成员id
     * </pre>
     */
    public int getMemerId() {
      return memerId_;
    }

    public static final int TITLE_FIELD_NUMBER = 2;
    private int title_;
    /**
     * <code>required int32 title = 2;</code>
     *
     * <pre>
     *成员封号
     * </pre>
     */
    public boolean hasTitle() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required int32 title = 2;</code>
     *
     * <pre>
     *成员封号
     * </pre>
     */
    public int getTitle() {
      return title_;
    }

    public static final int CONTRIBUTENUM_FIELD_NUMBER = 3;
    private int contributeNum_;
    /**
     * <code>required int32 contributeNum = 3;</code>
     *
     * <pre>
     *个人累计贡献
     * </pre>
     */
    public boolean hasContributeNum() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>required int32 contributeNum = 3;</code>
     *
     * <pre>
     *个人累计贡献
     * </pre>
     */
    public int getContributeNum() {
      return contributeNum_;
    }

    public static final int CURRCONTRIBUTENUM_FIELD_NUMBER = 4;
    private int currContributeNum_;
    /**
     * <code>required int32 currContributeNum = 4;</code>
     *
     * <pre>
     *个人当前剩余贡献
     * </pre>
     */
    public boolean hasCurrContributeNum() {
      return ((bitField0_ & 0x00000008) == 0x00000008);
    }
    /**
     * <code>required int32 currContributeNum = 4;</code>
     *
     * <pre>
     *个人当前剩余贡献
     * </pre>
     */
    public int getCurrContributeNum() {
      return currContributeNum_;
    }

    public static final int OLDCBNUM_FIELD_NUMBER = 5;
    private int oldCbNum_;
    /**
     * <code>required int32 oldCbNum = 5;</code>
     *
     * <pre>
     *个人昨日捐献
     * </pre>
     */
    public boolean hasOldCbNum() {
      return ((bitField0_ & 0x00000010) == 0x00000010);
    }
    /**
     * <code>required int32 oldCbNum = 5;</code>
     *
     * <pre>
     *个人昨日捐献
     * </pre>
     */
    public int getOldCbNum() {
      return oldCbNum_;
    }

    public static final int NEWCBNUM_FIELD_NUMBER = 6;
    private int newCbNum_;
    /**
     * <code>required int32 newCbNum = 6;</code>
     *
     * <pre>
     *个人今日零点截止到当前时间时间的 捐献总数量	
     * </pre>
     */
    public boolean hasNewCbNum() {
      return ((bitField0_ & 0x00000020) == 0x00000020);
    }
    /**
     * <code>required int32 newCbNum = 6;</code>
     *
     * <pre>
     *个人今日零点截止到当前时间时间的 捐献总数量	
     * </pre>
     */
    public int getNewCbNum() {
      return newCbNum_;
    }

    private void initFields() {
      memerId_ = 0;
      title_ = 0;
      contributeNum_ = 0;
      currContributeNum_ = 0;
      oldCbNum_ = 0;
      newCbNum_ = 0;
    }
    private byte memoizedIsInitialized = -1;
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      if (!hasMemerId()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasTitle()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasContributeNum()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasCurrContributeNum()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasOldCbNum()) {
        memoizedIsInitialized = 0;
        return false;
      }
      if (!hasNewCbNum()) {
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
        output.writeInt32(1, memerId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeInt32(2, title_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeInt32(3, contributeNum_);
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        output.writeInt32(4, currContributeNum_);
      }
      if (((bitField0_ & 0x00000010) == 0x00000010)) {
        output.writeInt32(5, oldCbNum_);
      }
      if (((bitField0_ & 0x00000020) == 0x00000020)) {
        output.writeInt32(6, newCbNum_);
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
          .computeInt32Size(1, memerId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(2, title_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(3, contributeNum_);
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(4, currContributeNum_);
      }
      if (((bitField0_ & 0x00000010) == 0x00000010)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(5, oldCbNum_);
      }
      if (((bitField0_ & 0x00000020) == 0x00000020)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(6, newCbNum_);
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

    public static com.protobuf.GuildMember.guild_member parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.GuildMember.guild_member parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.GuildMember.guild_member parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static com.protobuf.GuildMember.guild_member parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static com.protobuf.GuildMember.guild_member parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.GuildMember.guild_member parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }
    public static com.protobuf.GuildMember.guild_member parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input);
    }
    public static com.protobuf.GuildMember.guild_member parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseDelimitedFrom(input, extensionRegistry);
    }
    public static com.protobuf.GuildMember.guild_member parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return PARSER.parseFrom(input);
    }
    public static com.protobuf.GuildMember.guild_member parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return PARSER.parseFrom(input, extensionRegistry);
    }

    public static Builder newBuilder() { return Builder.create(); }
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder(com.protobuf.GuildMember.guild_member prototype) {
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
     * Protobuf type {@code guild_member}
     *
     * <pre>
     * 势力成员信息
     * </pre>
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessage.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:guild_member)
        com.protobuf.GuildMember.guild_memberOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return com.protobuf.GuildMember.internal_static_guild_member_descriptor;
      }

      protected com.google.protobuf.GeneratedMessage.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return com.protobuf.GuildMember.internal_static_guild_member_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                com.protobuf.GuildMember.guild_member.class, com.protobuf.GuildMember.guild_member.Builder.class);
      }

      // Construct using com.protobuf.GuildMember.guild_member.newBuilder()
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
        memerId_ = 0;
        bitField0_ = (bitField0_ & ~0x00000001);
        title_ = 0;
        bitField0_ = (bitField0_ & ~0x00000002);
        contributeNum_ = 0;
        bitField0_ = (bitField0_ & ~0x00000004);
        currContributeNum_ = 0;
        bitField0_ = (bitField0_ & ~0x00000008);
        oldCbNum_ = 0;
        bitField0_ = (bitField0_ & ~0x00000010);
        newCbNum_ = 0;
        bitField0_ = (bitField0_ & ~0x00000020);
        return this;
      }

      public Builder clone() {
        return create().mergeFrom(buildPartial());
      }

      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return com.protobuf.GuildMember.internal_static_guild_member_descriptor;
      }

      public com.protobuf.GuildMember.guild_member getDefaultInstanceForType() {
        return com.protobuf.GuildMember.guild_member.getDefaultInstance();
      }

      public com.protobuf.GuildMember.guild_member build() {
        com.protobuf.GuildMember.guild_member result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      public com.protobuf.GuildMember.guild_member buildPartial() {
        com.protobuf.GuildMember.guild_member result = new com.protobuf.GuildMember.guild_member(this);
        int from_bitField0_ = bitField0_;
        int to_bitField0_ = 0;
        if (((from_bitField0_ & 0x00000001) == 0x00000001)) {
          to_bitField0_ |= 0x00000001;
        }
        result.memerId_ = memerId_;
        if (((from_bitField0_ & 0x00000002) == 0x00000002)) {
          to_bitField0_ |= 0x00000002;
        }
        result.title_ = title_;
        if (((from_bitField0_ & 0x00000004) == 0x00000004)) {
          to_bitField0_ |= 0x00000004;
        }
        result.contributeNum_ = contributeNum_;
        if (((from_bitField0_ & 0x00000008) == 0x00000008)) {
          to_bitField0_ |= 0x00000008;
        }
        result.currContributeNum_ = currContributeNum_;
        if (((from_bitField0_ & 0x00000010) == 0x00000010)) {
          to_bitField0_ |= 0x00000010;
        }
        result.oldCbNum_ = oldCbNum_;
        if (((from_bitField0_ & 0x00000020) == 0x00000020)) {
          to_bitField0_ |= 0x00000020;
        }
        result.newCbNum_ = newCbNum_;
        result.bitField0_ = to_bitField0_;
        onBuilt();
        return result;
      }

      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof com.protobuf.GuildMember.guild_member) {
          return mergeFrom((com.protobuf.GuildMember.guild_member)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(com.protobuf.GuildMember.guild_member other) {
        if (other == com.protobuf.GuildMember.guild_member.getDefaultInstance()) return this;
        if (other.hasMemerId()) {
          setMemerId(other.getMemerId());
        }
        if (other.hasTitle()) {
          setTitle(other.getTitle());
        }
        if (other.hasContributeNum()) {
          setContributeNum(other.getContributeNum());
        }
        if (other.hasCurrContributeNum()) {
          setCurrContributeNum(other.getCurrContributeNum());
        }
        if (other.hasOldCbNum()) {
          setOldCbNum(other.getOldCbNum());
        }
        if (other.hasNewCbNum()) {
          setNewCbNum(other.getNewCbNum());
        }
        this.mergeUnknownFields(other.getUnknownFields());
        return this;
      }

      public final boolean isInitialized() {
        if (!hasMemerId()) {
          
          return false;
        }
        if (!hasTitle()) {
          
          return false;
        }
        if (!hasContributeNum()) {
          
          return false;
        }
        if (!hasCurrContributeNum()) {
          
          return false;
        }
        if (!hasOldCbNum()) {
          
          return false;
        }
        if (!hasNewCbNum()) {
          
          return false;
        }
        return true;
      }

      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        com.protobuf.GuildMember.guild_member parsedMessage = null;
        try {
          parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          parsedMessage = (com.protobuf.GuildMember.guild_member) e.getUnfinishedMessage();
          throw e;
        } finally {
          if (parsedMessage != null) {
            mergeFrom(parsedMessage);
          }
        }
        return this;
      }
      private int bitField0_;

      private int memerId_ ;
      /**
       * <code>required int32 memerId = 1;</code>
       *
       * <pre>
       *成员id
       * </pre>
       */
      public boolean hasMemerId() {
        return ((bitField0_ & 0x00000001) == 0x00000001);
      }
      /**
       * <code>required int32 memerId = 1;</code>
       *
       * <pre>
       *成员id
       * </pre>
       */
      public int getMemerId() {
        return memerId_;
      }
      /**
       * <code>required int32 memerId = 1;</code>
       *
       * <pre>
       *成员id
       * </pre>
       */
      public Builder setMemerId(int value) {
        bitField0_ |= 0x00000001;
        memerId_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required int32 memerId = 1;</code>
       *
       * <pre>
       *成员id
       * </pre>
       */
      public Builder clearMemerId() {
        bitField0_ = (bitField0_ & ~0x00000001);
        memerId_ = 0;
        onChanged();
        return this;
      }

      private int title_ ;
      /**
       * <code>required int32 title = 2;</code>
       *
       * <pre>
       *成员封号
       * </pre>
       */
      public boolean hasTitle() {
        return ((bitField0_ & 0x00000002) == 0x00000002);
      }
      /**
       * <code>required int32 title = 2;</code>
       *
       * <pre>
       *成员封号
       * </pre>
       */
      public int getTitle() {
        return title_;
      }
      /**
       * <code>required int32 title = 2;</code>
       *
       * <pre>
       *成员封号
       * </pre>
       */
      public Builder setTitle(int value) {
        bitField0_ |= 0x00000002;
        title_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required int32 title = 2;</code>
       *
       * <pre>
       *成员封号
       * </pre>
       */
      public Builder clearTitle() {
        bitField0_ = (bitField0_ & ~0x00000002);
        title_ = 0;
        onChanged();
        return this;
      }

      private int contributeNum_ ;
      /**
       * <code>required int32 contributeNum = 3;</code>
       *
       * <pre>
       *个人累计贡献
       * </pre>
       */
      public boolean hasContributeNum() {
        return ((bitField0_ & 0x00000004) == 0x00000004);
      }
      /**
       * <code>required int32 contributeNum = 3;</code>
       *
       * <pre>
       *个人累计贡献
       * </pre>
       */
      public int getContributeNum() {
        return contributeNum_;
      }
      /**
       * <code>required int32 contributeNum = 3;</code>
       *
       * <pre>
       *个人累计贡献
       * </pre>
       */
      public Builder setContributeNum(int value) {
        bitField0_ |= 0x00000004;
        contributeNum_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required int32 contributeNum = 3;</code>
       *
       * <pre>
       *个人累计贡献
       * </pre>
       */
      public Builder clearContributeNum() {
        bitField0_ = (bitField0_ & ~0x00000004);
        contributeNum_ = 0;
        onChanged();
        return this;
      }

      private int currContributeNum_ ;
      /**
       * <code>required int32 currContributeNum = 4;</code>
       *
       * <pre>
       *个人当前剩余贡献
       * </pre>
       */
      public boolean hasCurrContributeNum() {
        return ((bitField0_ & 0x00000008) == 0x00000008);
      }
      /**
       * <code>required int32 currContributeNum = 4;</code>
       *
       * <pre>
       *个人当前剩余贡献
       * </pre>
       */
      public int getCurrContributeNum() {
        return currContributeNum_;
      }
      /**
       * <code>required int32 currContributeNum = 4;</code>
       *
       * <pre>
       *个人当前剩余贡献
       * </pre>
       */
      public Builder setCurrContributeNum(int value) {
        bitField0_ |= 0x00000008;
        currContributeNum_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required int32 currContributeNum = 4;</code>
       *
       * <pre>
       *个人当前剩余贡献
       * </pre>
       */
      public Builder clearCurrContributeNum() {
        bitField0_ = (bitField0_ & ~0x00000008);
        currContributeNum_ = 0;
        onChanged();
        return this;
      }

      private int oldCbNum_ ;
      /**
       * <code>required int32 oldCbNum = 5;</code>
       *
       * <pre>
       *个人昨日捐献
       * </pre>
       */
      public boolean hasOldCbNum() {
        return ((bitField0_ & 0x00000010) == 0x00000010);
      }
      /**
       * <code>required int32 oldCbNum = 5;</code>
       *
       * <pre>
       *个人昨日捐献
       * </pre>
       */
      public int getOldCbNum() {
        return oldCbNum_;
      }
      /**
       * <code>required int32 oldCbNum = 5;</code>
       *
       * <pre>
       *个人昨日捐献
       * </pre>
       */
      public Builder setOldCbNum(int value) {
        bitField0_ |= 0x00000010;
        oldCbNum_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required int32 oldCbNum = 5;</code>
       *
       * <pre>
       *个人昨日捐献
       * </pre>
       */
      public Builder clearOldCbNum() {
        bitField0_ = (bitField0_ & ~0x00000010);
        oldCbNum_ = 0;
        onChanged();
        return this;
      }

      private int newCbNum_ ;
      /**
       * <code>required int32 newCbNum = 6;</code>
       *
       * <pre>
       *个人今日零点截止到当前时间时间的 捐献总数量	
       * </pre>
       */
      public boolean hasNewCbNum() {
        return ((bitField0_ & 0x00000020) == 0x00000020);
      }
      /**
       * <code>required int32 newCbNum = 6;</code>
       *
       * <pre>
       *个人今日零点截止到当前时间时间的 捐献总数量	
       * </pre>
       */
      public int getNewCbNum() {
        return newCbNum_;
      }
      /**
       * <code>required int32 newCbNum = 6;</code>
       *
       * <pre>
       *个人今日零点截止到当前时间时间的 捐献总数量	
       * </pre>
       */
      public Builder setNewCbNum(int value) {
        bitField0_ |= 0x00000020;
        newCbNum_ = value;
        onChanged();
        return this;
      }
      /**
       * <code>required int32 newCbNum = 6;</code>
       *
       * <pre>
       *个人今日零点截止到当前时间时间的 捐献总数量	
       * </pre>
       */
      public Builder clearNewCbNum() {
        bitField0_ = (bitField0_ & ~0x00000020);
        newCbNum_ = 0;
        onChanged();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:guild_member)
    }

    static {
      defaultInstance = new guild_member(true);
      defaultInstance.initFields();
    }

    // @@protoc_insertion_point(class_scope:guild_member)
  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_guild_member_descriptor;
  private static
    com.google.protobuf.GeneratedMessage.FieldAccessorTable
      internal_static_guild_member_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\022guild_member.proto\"\204\001\n\014guild_member\022\017\n" +
      "\007memerId\030\001 \002(\005\022\r\n\005title\030\002 \002(\005\022\025\n\rcontrib" +
      "uteNum\030\003 \002(\005\022\031\n\021currContributeNum\030\004 \002(\005\022" +
      "\020\n\010oldCbNum\030\005 \002(\005\022\020\n\010newCbNum\030\006 \002(\005B\016\n\014c" +
      "om.protobuf"
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
    internal_static_guild_member_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_guild_member_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessage.FieldAccessorTable(
        internal_static_guild_member_descriptor,
        new java.lang.String[] { "MemerId", "Title", "ContributeNum", "CurrContributeNum", "OldCbNum", "NewCbNum", });
  }

  // @@protoc_insertion_point(outer_class_scope)
}
