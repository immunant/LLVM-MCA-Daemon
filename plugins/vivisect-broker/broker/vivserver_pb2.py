# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: vivserver.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x0fvivserver.proto\"1\n\x16RunInstructionsRequest\x12\x17\n\x0fnumInstructions\x18\x01 \x01(\x05\"K\n\x0cMemoryAccess\x12\r\n\x05index\x18\x01 \x01(\r\x12\r\n\x05vAddr\x18\x02 \x01(\x04\x12\x0c\n\x04size\x18\x03 \x01(\r\x12\x0f\n\x07isStore\x18\x04 \x01(\x08\"\xbe\x01\n\x14RunInstructionsReply\x12\x37\n\x0cinstructions\x18\x01 \x03(\x0b\x32!.RunInstructionsReply.Instruction\x1am\n\x0bInstruction\x12\x13\n\x0binstruction\x18\x01 \x01(\x0c\x12\x0e\n\x06opCode\x18\x02 \x01(\x0c\x12(\n\x0cmemoryAccess\x18\x03 \x01(\x0b\x32\r.MemoryAccessH\x00\x88\x01\x01\x42\x0f\n\r_memoryAccess2R\n\x08\x45mulator\x12\x46\n\x12RunNumInstructions\x12\x17.RunInstructionsRequest\x1a\x15.RunInstructionsReply\"\x00\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'vivserver_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_RUNINSTRUCTIONSREQUEST']._serialized_start=19
  _globals['_RUNINSTRUCTIONSREQUEST']._serialized_end=68
  _globals['_MEMORYACCESS']._serialized_start=70
  _globals['_MEMORYACCESS']._serialized_end=145
  _globals['_RUNINSTRUCTIONSREPLY']._serialized_start=148
  _globals['_RUNINSTRUCTIONSREPLY']._serialized_end=338
  _globals['_RUNINSTRUCTIONSREPLY_INSTRUCTION']._serialized_start=229
  _globals['_RUNINSTRUCTIONSREPLY_INSTRUCTION']._serialized_end=338
  _globals['_EMULATOR']._serialized_start=340
  _globals['_EMULATOR']._serialized_end=422
# @@protoc_insertion_point(module_scope)
