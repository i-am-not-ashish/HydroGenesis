#ifndef WATER_LEVEL_MODEL_H
#define WATER_LEVEL_MODEL_H

alignas(8) const unsigned char water_level_model_tflite[] = {
  0x1c, 0x00, 0x00, 0x00, 0x54, 0x46, 0x4c, 0x33, 0x14, 0x00, 0x20, 0x00,
  0x1c, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x98, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0xdc, 0x02, 0x00, 0x00,
  0xec, 0x02, 0x00, 0x00, 0x7c, 0x06, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x00,
  0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x73, 0x65, 0x72, 0x76, 0x69, 0x6e, 0x67, 0x5f,
  0x64, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x90, 0xff, 0xff, 0xff, 0x06, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x6f, 0x75, 0x74, 0x70,
  0x75, 0x74, 0x5f, 0x30, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xda, 0xfd, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x6b, 0x65, 0x72, 0x61, 0x73, 0x5f, 0x74, 0x65,
  0x6e, 0x73, 0x6f, 0x72, 0x5f, 0x33, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x34, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xdc, 0xff, 0xff, 0xff,
  0x09, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
  0x43, 0x4f, 0x4e, 0x56, 0x45, 0x52, 0x53, 0x49, 0x4f, 0x4e, 0x5f, 0x4d,
  0x45, 0x54, 0x41, 0x44, 0x41, 0x54, 0x41, 0x00, 0x08, 0x00, 0x0c, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x6d, 0x69, 0x6e, 0x5f,
  0x72, 0x75, 0x6e, 0x74, 0x69, 0x6d, 0x65, 0x5f, 0x76, 0x65, 0x72, 0x73,
  0x69, 0x6f, 0x6e, 0x00, 0x0a, 0x00, 0x00, 0x00, 0xe8, 0x01, 0x00, 0x00,
  0xe0, 0x01, 0x00, 0x00, 0xa8, 0x01, 0x00, 0x00, 0x8c, 0x01, 0x00, 0x00,
  0x54, 0x01, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x00,
  0x94, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x7e, 0xfe, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0e, 0x00, 0x08, 0x00, 0x04, 0x00,
  0x08, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xea, 0x03, 0x00, 0x00,
  0x0c, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x04, 0x00,
  0x0c, 0x00, 0x00, 0x00, 0xcd, 0xf2, 0x84, 0xda, 0x0b, 0x1a, 0x81, 0xa8,
  0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x32, 0x2e, 0x31, 0x39, 0x2e, 0x30, 0x00, 0x00,
  0xea, 0xfe, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x31, 0x2e, 0x35, 0x2e, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x58, 0xfb, 0xff, 0xff, 0x5c, 0xfb, 0xff, 0xff,
  0x0e, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00,
  0x58, 0x2f, 0xe9, 0xbd, 0xba, 0xbf, 0x51, 0x3f, 0x2a, 0x6d, 0x9d, 0x3e,
  0x64, 0x2c, 0x2e, 0x3e, 0xaf, 0x0b, 0xb6, 0xbe, 0x19, 0xd8, 0xcb, 0x3e,
  0x2d, 0x9e, 0x34, 0x3f, 0x83, 0xf2, 0x8a, 0xbe, 0x78, 0xfb, 0x24, 0xbe,
  0x86, 0x91, 0xdb, 0xbe, 0x0e, 0x40, 0x13, 0xbf, 0x0e, 0x91, 0x7a, 0xbe,
  0x5e, 0x65, 0xd2, 0x3d, 0x8a, 0xb2, 0xdb, 0x3e, 0xfe, 0xd0, 0x7e, 0xbd,
  0x74, 0x65, 0xab, 0xbe, 0x61, 0x9a, 0x75, 0x3d, 0x56, 0x04, 0xe3, 0x3d,
  0x06, 0x81, 0x72, 0x3e, 0x97, 0x9a, 0x10, 0x3f, 0xfb, 0xc1, 0x96, 0x3e,
  0x79, 0x2d, 0x53, 0x3e, 0xe0, 0xa9, 0x36, 0x3e, 0x22, 0x21, 0xae, 0xbe,
  0x36, 0x11, 0xe7, 0x3b, 0x0e, 0x6f, 0xf2, 0x3e, 0x6c, 0x64, 0xcd, 0x3e,
  0xf1, 0xb8, 0x59, 0x3f, 0x07, 0x74, 0xb8, 0xbe, 0x00, 0xab, 0xa3, 0xbb,
  0x7e, 0x93, 0xdb, 0xbe, 0x70, 0xd2, 0x12, 0x3d, 0xf3, 0x64, 0x4d, 0x3f,
  0x99, 0xc5, 0x1c, 0x3f, 0x48, 0x4d, 0xfd, 0x3d, 0x13, 0x05, 0x50, 0x3f,
  0xfb, 0xce, 0x95, 0xbe, 0xe9, 0x39, 0xbb, 0x3e, 0x58, 0x6a, 0xd9, 0x3e,
  0x52, 0x14, 0xe8, 0xbd, 0xba, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00,
  0x28, 0x00, 0x00, 0x00, 0xab, 0x46, 0x80, 0x3e, 0xfe, 0x0b, 0x8d, 0x3e,
  0x00, 0x00, 0x00, 0x00, 0x2d, 0x5a, 0x16, 0xbe, 0x73, 0x2d, 0x8b, 0x3e,
  0x9d, 0x5a, 0x32, 0xbe, 0x93, 0xfe, 0x6b, 0x3e, 0x00, 0x00, 0x00, 0x00,
  0x63, 0xe8, 0x5c, 0x3e, 0xb1, 0x11, 0x96, 0x3e, 0xee, 0xff, 0xff, 0xff,
  0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xcb, 0xae, 0x4c, 0x3e,
  0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0xd6, 0xff, 0xe4, 0x3e,
  0x68, 0xe6, 0x0d, 0x3f, 0xc1, 0xc0, 0x08, 0x3f, 0xb7, 0x99, 0x53, 0xbe,
  0x62, 0x68, 0xe1, 0x3e, 0xac, 0xaf, 0x19, 0xbf, 0x92, 0x84, 0xeb, 0x3e,
  0x5c, 0xe4, 0x2b, 0xbf, 0xcd, 0xf7, 0x31, 0x3f, 0x21, 0xd6, 0x3d, 0x3f,
  0x8c, 0xfc, 0xff, 0xff, 0x90, 0xfc, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00,
  0x4d, 0x4c, 0x49, 0x52, 0x20, 0x43, 0x6f, 0x6e, 0x76, 0x65, 0x72, 0x74,
  0x65, 0x64, 0x2e, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0e, 0x00, 0x18, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00,
  0x08, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00,
  0xa8, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0xce, 0xff, 0xff, 0xff, 0x10, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x04, 0xfd, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x16, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x04, 0x00, 0x0e, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x07, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x06, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0x00, 0x00, 0x00, 0x58, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
  0xac, 0x01, 0x00, 0x00, 0x50, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x60, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0xda, 0xfd, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x01, 0x14, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x34, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
  0xc4, 0xfd, 0xff, 0xff, 0x1b, 0x00, 0x00, 0x00, 0x53, 0x74, 0x61, 0x74,
  0x65, 0x66, 0x75, 0x6c, 0x50, 0x61, 0x72, 0x74, 0x69, 0x74, 0x69, 0x6f,
  0x6e, 0x65, 0x64, 0x43, 0x61, 0x6c, 0x6c, 0x5f, 0x31, 0x3a, 0x30, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x32, 0xfe, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x14, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
  0x78, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
  0x0a, 0x00, 0x00, 0x00, 0x1c, 0xfe, 0xff, 0xff, 0x5e, 0x00, 0x00, 0x00,
  0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31,
  0x5f, 0x31, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32, 0x5f, 0x31,
  0x2f, 0x4d, 0x61, 0x74, 0x4d, 0x75, 0x6c, 0x3b, 0x73, 0x65, 0x71, 0x75,
  0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31, 0x5f, 0x31, 0x2f, 0x64,
  0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32, 0x5f, 0x31, 0x2f, 0x52, 0x65, 0x6c,
  0x75, 0x3b, 0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c,
  0x5f, 0x31, 0x5f, 0x31, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32,
  0x5f, 0x31, 0x2f, 0x42, 0x69, 0x61, 0x73, 0x41, 0x64, 0x64, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x22, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00,
  0xa8, 0xfe, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x73, 0x65, 0x71, 0x75,
  0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31, 0x5f, 0x31, 0x2f, 0x64,
  0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32, 0x5f, 0x31, 0x2f, 0x4d, 0x61, 0x74,
  0x4d, 0x75, 0x6c, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x6e, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01,
  0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
  0x3c, 0x00, 0x00, 0x00, 0xf4, 0xfe, 0xff, 0xff, 0x2f, 0x00, 0x00, 0x00,
  0x73, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x74, 0x69, 0x61, 0x6c, 0x5f, 0x31,
  0x5f, 0x31, 0x2f, 0x64, 0x65, 0x6e, 0x73, 0x65, 0x5f, 0x32, 0x5f, 0x31,
  0x2f, 0x42, 0x69, 0x61, 0x73, 0x41, 0x64, 0x64, 0x2f, 0x52, 0x65, 0x61,
  0x64, 0x56, 0x61, 0x72, 0x69, 0x61, 0x62, 0x6c, 0x65, 0x4f, 0x70, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0xc6, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x4c, 0xff, 0xff, 0xff,
  0x0f, 0x00, 0x00, 0x00, 0x61, 0x72, 0x69, 0x74, 0x68, 0x2e, 0x63, 0x6f,
  0x6e, 0x73, 0x74, 0x61, 0x6e, 0x74, 0x31, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x18, 0x00, 0x14, 0x00,
  0x00, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x1c, 0x00, 0x00, 0x00, 0x9c, 0xff, 0xff, 0xff, 0x0e, 0x00, 0x00, 0x00,
  0x61, 0x72, 0x69, 0x74, 0x68, 0x2e, 0x63, 0x6f, 0x6e, 0x73, 0x74, 0x61,
  0x6e, 0x74, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x1c, 0x00, 0x18, 0x00,
  0x00, 0x00, 0x14, 0x00, 0x10, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x00, 0x07, 0x00, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x14, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00,
  0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x73, 0x65, 0x72, 0x76,
  0x69, 0x6e, 0x67, 0x5f, 0x64, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x5f,
  0x6b, 0x65, 0x72, 0x61, 0x73, 0x5f, 0x74, 0x65, 0x6e, 0x73, 0x6f, 0x72,
  0x5f, 0x33, 0x3a, 0x30, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x0c, 0x00, 0x0b, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x09
};

const unsigned int water_level_model_tflite_len = 1744;

#endif
