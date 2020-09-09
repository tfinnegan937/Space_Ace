Lights1 skybox_sm64_material_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFE, 0xFE, 0xFE, 0x28, 0x28, 0x28);

Gfx skybox_space_texture_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 skybox_space_texture_rgba16[] = {
	0x52, 0x9D, 0x49, 0xD9, 0x41, 0xD9, 0x31, 0x97, 0x31, 
	0x93, 0x21, 0x4F, 0x21, 0x8F, 0x29, 0x8F, 0x39, 0xD3, 
	0x49, 0xD9, 0x51, 0x9B, 0x49, 0xDD, 0x31, 0x59, 0x31, 
	0x55, 0x31, 0x11, 0x31, 0x4F, 0x18, 0xC9, 0x21, 0xB, 
	0x29, 0x4F, 0x28, 0xD1, 0x41, 0x17, 0x51, 0x1B, 0x41, 
	0x17, 0x29, 0x11, 0x21, 0x13, 0x29, 0x51, 0x29, 0x4F, 
	0x21, 0xD, 0x29, 0xF, 0x29, 0x11, 0x39, 0xD7, 0x31, 
	0x53, 0x3A, 0x57, 0x39, 0x97, 0x41, 0x99, 0x31, 0x55, 
	0x21, 0x4F, 0x19, 0xD, 0x19, 0xB, 0x19, 0xB, 0x29, 
	0x51, 0x31, 0x53, 0x39, 0x57, 0x29, 0x59, 0x21, 0x17, 
	0x29, 0x13, 0x29, 0xF, 0x10, 0x87, 0x18, 0xC9, 0x10, 
	0x89, 0x10, 0x8B, 0x18, 0x8D, 0x30, 0xD3, 0x48, 0xD9, 
	0x48, 0xD9, 0x28, 0xD1, 0x20, 0xCF, 0x18, 0xCD, 0x18, 
	0x8B, 0x10, 0x8B, 0x10, 0x8B, 0x20, 0xCF, 0x20, 0xD1, 
	0x21, 0xF, 0x32, 0x17, 0x29, 0x53, 0x39, 0x97, 0x31, 
	0x55, 0x21, 0x51, 0x19, 0xB, 0x19, 0xB, 0x19, 0xB, 
	0x19, 0xD, 0x29, 0x11, 0x29, 0x13, 0x29, 0x55, 0x21, 
	0x15, 0x29, 0x13, 0x18, 0xCD, 0x10, 0x87, 0x10, 0x89, 
	0x10, 0x89, 0x18, 0xCB, 0x20, 0xCF, 0x28, 0xD3, 0x40, 
	0xD9, 0x49, 0x5B, 0x30, 0xD3, 0x18, 0x8D, 0x18, 0x8B, 
	0x10, 0x89, 0x10, 0x89, 0x18, 0x8B, 0x18, 0x8D, 0x18, 
	0x4D, 0x20, 0xCF, 0x32, 0x15, 0x21, 0x93, 0x29, 0xD5, 
	0x29, 0x95, 0x21, 0x53, 0x19, 0x4F, 0x21, 0x4F, 0x19, 
	0xF, 0x19, 0xD, 0x21, 0xF, 0x21, 0x11, 0x18, 0xCF, 
	0x18, 0xCF, 0x18, 0xD1, 0x18, 0xCD, 0x10, 0x89, 0x10, 
	0x89, 0x10, 0x47, 0x10, 0x8B, 0x18, 0x91, 0x28, 0xD5, 
	0x39, 0x17, 0x52, 0x5F, 0x28, 0xD1, 0x20, 0xCB, 0x10, 
	0x87, 0x8, 0x47, 0x8, 0x47, 0x10, 0x87, 0x18, 0x89, 
	0x18, 0x8D, 0x20, 0xD1, 0x29, 0x91, 0x21, 0xD5, 0x2A, 
	0x19, 0x2A, 0x1B, 0x29, 0x99, 0x21, 0x53, 0x19, 0x4F, 
	0x21, 0x51, 0x19, 0xF, 0x19, 0xD, 0x18, 0xCF, 0x18, 
	0xCD, 0x10, 0x8D, 0x10, 0x8F, 0x10, 0x8D, 0x10, 0x8B, 
	0x8, 0x47, 0x8, 0x49, 0x10, 0x4D, 0x18, 0x91, 0x20, 
	0xD5, 0x30, 0xD3, 0x28, 0xD1, 0x18, 0x8B, 0x10, 0x49, 
	0x10, 0x47, 0x8, 0x45, 0x8, 0x45, 0x10, 0x87, 0x10, 
	0x47, 0x18, 0x8D, 0x20, 0xD1, 0x21, 0xF, 0x19, 0x51, 
	0x32, 0x5B, 0x32, 0x1B, 0x29, 0xD9, 0x21, 0x95, 0x19, 
	0x51, 0x19, 0x51, 0x19, 0xF, 0x19, 0xD, 0x19, 0xD, 
	0x18, 0xCF, 0x18, 0xCF, 0x10, 0x8F, 0x10, 0x8F, 0x10, 
	0x8B, 0x8, 0x89, 0x10, 0x8B, 0x10, 0x8F, 0x18, 0x91, 
	0x20, 0x91, 0x20, 0x91, 0x18, 0x8D, 0x10, 0x49, 0x8, 
	0x47, 0x10, 0x47, 0x10, 0x49, 0x10, 0x49, 0x10, 0x47, 
	0x10, 0x89, 0x18, 0x8D, 0x28, 0xD1, 0x29, 0xF, 0x19, 
	0x11, 0x2A, 0x19, 0x3A, 0x1B, 0x29, 0x97, 0x21, 0x97, 
	0x21, 0x53, 0x19, 0x51, 0x19, 0x91, 0x19, 0xD1, 0x19, 
	0x4F, 0x21, 0x51, 0x21, 0x11, 0x10, 0xCF, 0x10, 0xD1, 
	0x10, 0x8F, 0x10, 0x8B, 0x10, 0x8B, 0x10, 0x8D, 0x20, 
	0xD1, 0x20, 0x91, 0x20, 0x8F, 0x18, 0x8B, 0x8, 0x47, 
	0x8, 0x47, 0x10, 0x89, 0x18, 0x8B, 0x10, 0x4B, 0x18, 
	0x8B, 0x18, 0x8B, 0x28, 0x8F, 0x30, 0xCF, 0x29, 0x51, 
	0x21, 0x11, 0x29, 0xD9, 0x32, 0x5B, 0x2A, 0x19, 0x21, 
	0x99, 0x21, 0x55, 0x19, 0x4F, 0x19, 0xD3, 0x22, 0x55, 
	0x22, 0x55, 0x2A, 0x17, 0x29, 0xD7, 0x21, 0x93, 0x19, 
	0x55, 0x10, 0xD3, 0x10, 0x8D, 0x10, 0x89, 0x18, 0x8B, 
	0x20, 0xCF, 0x20, 0xCF, 0x20, 0xCB, 0x18, 0x89, 0x10, 
	0x47, 0x10, 0x89, 0x10, 0x89, 0x10, 0x89, 0x18, 0x4B, 
	0x20, 0x8D, 0x28, 0x8F, 0x28, 0x8F, 0x20, 0xCB, 0x29, 
	0x55, 0x21, 0x13, 0x21, 0x55, 0x2A, 0x19, 0x32, 0x5D, 
	0x32, 0x5D, 0x32, 0x1B, 0x21, 0xD5, 0x22, 0x15, 0x2A, 
	0x97, 0x32, 0xD9, 0x32, 0x9B, 0x2A, 0x57, 0x2A, 0x17, 
	0x22, 0x1B, 0x21, 0x99, 0x10, 0xCF, 0x18, 0x89, 0x20, 
	0x8B, 0x28, 0x8F, 0x20, 0x8D, 0x18, 0x89, 0x20, 0x8B, 
	0x10, 0x47, 0x10, 0x89, 0x10, 0x8B, 0x10, 0x89, 0x18, 
	0x49, 0x28, 0xCF, 0x28, 0x91, 0x18, 0x4B, 0x20, 0xCB, 
	0x39, 0xD7, 0x29, 0x55, 0x21, 0x53, 0x29, 0x97, 0x3A, 
	0x5D, 0x42, 0xE3, 0x42, 0xE3, 0x42, 0xDF, 0x32, 0x59, 
	0x32, 0x9B, 0x3B, 0x1D, 0x33, 0x1D, 0x2A, 0xD9, 0x2A, 
	0x59, 0x2A, 0x9D, 0x2A, 0x1B, 0x21, 0x51, 0x18, 0xCB, 
	0x28, 0x8D, 0x38, 0x91, 0x30, 0xCF, 0x20, 0x4B, 0x18, 
	0x8B, 0x18, 0x89, 0x18, 0xCB, 0x10, 0x47, 0x10, 0x47, 
	0x18, 0x8B, 0x28, 0xD1, 0x20, 0xCD, 0x10, 0x89, 0x20, 
	0xCB, 0x39, 0xD7, 0x29, 0x95, 0x21, 0x53, 0x21, 0x53, 
	0x31, 0xD9, 0x4A, 0x9F, 0x53, 0x23, 0x4B, 0x63, 0x3A, 
	0x9D, 0x32, 0x59, 0x3A, 0xDB, 0x33, 0x1B, 0x33, 0x1B, 
	0x2A, 0x99, 0x2A, 0x59, 0x2A, 0x59, 0x21, 0x95, 0x19, 
	0xD, 0x28, 0xCD, 0x38, 0xD1, 0x38, 0xD1, 0x30, 0x8F, 
	0x20, 0x8D, 0x20, 0x8B, 0x18, 0x8B, 0x10, 0x47, 0x10, 
	0x89, 0x10, 0x4B, 0x20, 0x8F, 0x20, 0x8D, 0x18, 0x8B, 
	0x21, 0xD, 0x29, 0x51, 0x21, 0x4F, 0x21, 0x51, 0x21, 
	0x53, 0x31, 0x95, 0x41, 0xD9, 0x42, 0x5B, 0x3A, 0x5B, 
	0x32, 0x5B, 0x2A, 0x19, 0x3A, 0x9B, 0x33, 0x1D, 0x43, 
	0xA1, 0x33, 0x1B, 0x2A, 0x15, 0x2A, 0x15, 0x2A, 0x17, 
	0x21, 0xD3, 0x21, 0x4F, 0x29, 0x11, 0x30, 0xD3, 0x41, 
	0x15, 0x30, 0xD1, 0x28, 0xCF, 0x20, 0xCD, 0x10, 0x89, 
	0x10, 0x47, 0x10, 0x49, 0x18, 0x8B, 0x20, 0x8D, 0x18, 
	0x8D, 0x21, 0xF, 0x31, 0xD3, 0x21, 0x4F, 0x19, 0x4D, 
	0x21, 0x51, 0x29, 0x95, 0x31, 0x95, 0x39, 0xD7, 0x29, 
	0x95, 0x21, 0x53, 0x31, 0xD5, 0x32, 0x59, 0x43, 0xA1, 
	0x4C, 0x23, 0x43, 0x9F, 0x2A, 0x17, 0x2A, 0x13, 0x29, 
	0xD5, 0x2A, 0x55, 0x29, 0xD3, 0x29, 0x93, 0x31, 0x15, 
	0x39, 0x17, 0x39, 0x15, 0x31, 0x11, 0x28, 0xCD, 0x20, 
	0xCB, 0x18, 0x49, 0x10, 0x49, 0x18, 0x8B, 0x20, 0x8D, 
	0x20, 0x8F, 0x21, 0xF, 0x39, 0x95, 0x21, 0xF, 0x19, 
	0xD, 0x19, 0x4D, 0x21, 0x51, 0x31, 0xD5, 0x3A, 0x15, 
	0x21, 0x51, 0x21, 0x53, 0x31, 0xD5, 0x3A, 0x59, 0x4B, 
	0xE3, 0x5C, 0xA7, 0x4B, 0xA1, 0x3A, 0x59, 0x32, 0x15, 
	0x2A, 0x15, 0x32, 0x99, 0x2A, 0x15, 0x29, 0x93, 0x29, 
	0x53, 0x31, 0x15, 0x31, 0x53, 0x20, 0xCF, 0x20, 0xCD, 
	0x28, 0xCF, 0x20, 0xCD, 0x18, 0x89, 0x18, 0x4B, 0x18, 
	0x8D, 0x20, 0x8D, 0x31, 0x11, 0x31, 0x95, 0x29, 0x51, 
	0x21, 0xD, 0x11, 0xB, 0x19, 0x4F, 0x21, 0x4F, 0x3A, 
	0x13, 0x29, 0x95, 0x29, 0xD5, 0x29, 0xD5, 0x32, 0x57, 
	0x43, 0x61, 0x53, 0xE3, 0x4B, 0xA1, 0x32, 0x99, 0x32, 
	0x57, 0x32, 0x99, 0x3B, 0xA1, 0x33, 0x1D, 0x3A, 0x9B, 
	0x32, 0x17, 0x29, 0x53, 0x21, 0x11, 0x21, 0xF, 0x21, 
	0xF, 0x29, 0xF, 0x29, 0xF, 0x28, 0xCD, 0x20, 0x8B, 
	0x20, 0x8D, 0x20, 0x8B, 0x31, 0x11, 0x39, 0xD9, 0x29, 
	0x51, 0x29, 0x51, 0x29, 0x51, 0x21, 0x4F, 0x29, 0xD1, 
	0x3A, 0x99, 0x43, 0x5F, 0x43, 0x1F, 0x3A, 0x9B, 0x3A, 
	0x9D, 0x53, 0xA3, 0x4B, 0xE3, 0x4B, 0xE3, 0x3B, 0x1B, 
	0x3A, 0xDB, 0x4B, 0x61, 0x5D, 0x2B, 0x4C, 0xA7, 0x43, 
	0xE3, 0x3A, 0xDF, 0x32, 0x5B, 0x29, 0xD5, 0x29, 0x95, 
	0x29, 0x93, 0x31, 0xD5, 0x3A, 0x17, 0x31, 0x53, 0x20, 
	0xCF, 0x20, 0xCD, 0x20, 0x8D, 0x31, 0x11, 0x39, 0xDB, 
	0x31, 0xD5, 0x31, 0x95, 0x31, 0x93, 0x21, 0x51, 0x32, 
	0x55, 0x54, 0x23, 0x75, 0xB1, 0x64, 0xAB, 0x4B, 0x63, 
	0x5B, 0x63, 0x4B, 0x63, 0x4B, 0x61, 0x43, 0x61, 0x32, 
	0xDB, 0x32, 0xDB, 0x4B, 0xE3, 0x65, 0x6F, 0x54, 0xEB, 
	0x3B, 0xA1, 0x3A, 0xDD, 0x3A, 0x9D, 0x32, 0x9B, 0x32, 
	0x9F, 0x3A, 0x9F, 0x42, 0xDF, 0x53, 0x1F, 0x41, 0xD7, 
	0x31, 0x51, 0x31, 0x51, 0x31, 0x51, 0x31, 0x51, 0x42, 
	0x1D, 0x31, 0xD9, 0x31, 0xD7, 0x31, 0x93, 0x29, 0x51, 
	0x32, 0x57, 0x4C, 0x23, 0x75, 0xF3, 0x54, 0x67, 0x3A, 
	0xDF, 0x42, 0x9F, 0x3A, 0x5D, 0x32, 0x5B, 0x2A, 0x5B, 
	0x3A, 0x9D, 0x32, 0x9B, 0x3B, 0x21, 0x4C, 0x25, 0x43, 
	0xE5, 0x3A, 0x9D, 0x3A, 0x19, 0x3A, 0x19, 0x29, 0xD9, 
	0x3A, 0xA1, 0x53, 0x65, 0x4B, 0x23, 0x52, 0xDF, 0x39, 
	0xD7, 0x31, 0x93, 0x31, 0xD3, 0x31, 0xD5, 0x3A, 0x17, 
	0x42, 0x5D, 0x31, 0xD9, 0x31, 0x97, 0x29, 0x55, 0x29, 
	0x95, 0x22, 0x17, 0x33, 0x1D, 0x4C, 0x23, 0x3B, 0x1B, 
	0x29, 0xD5, 0x32, 0x17, 0x32, 0x19, 0x32, 0x19, 0x32, 
	0x5B, 0x32, 0x1B, 0x3A, 0x19, 0x2A, 0x17, 0x32, 0x59, 
	0x3A, 0x9D, 0x42, 0x1B, 0x41, 0xD9, 0x29, 0x95, 0x29, 
	0x99, 0x39, 0xDD, 0x52, 0x21, 0x42, 0x1D, 0x3A, 0x19, 
	0x32, 0x17, 0x3A, 0xDB, 0x54, 0xA7, 0x5C, 0x67, 0x4B, 
	0x5F, 0x31, 0xDB, 0x29, 0x99, 0x31, 0x99, 0x31, 0x99, 
	0x29, 0x99, 0x2A, 0x17, 0x2A, 0x59, 0x2A, 0x99, 0x32, 
	0x15, 0x29, 0xD5, 0x32, 0x19, 0x32, 0x1B, 0x32, 0x1B, 
	0x32, 0x19, 0x29, 0x97, 0x21, 0x53, 0x29, 0x91, 0x29, 
	0x91, 0x29, 0x51, 0x41, 0x99, 0x41, 0x99, 0x31, 0x95, 
	0x42, 0x5D, 0x49, 0xDD, 0x49, 0x9D, 0x41, 0x99, 0x31, 
	0x53, 0x19, 0xD, 0x2A, 0x57, 0x6D, 0xAF, 0x6D, 0xAF, 
	0x54, 0x67, 0x31, 0xD9, 0x29, 0x97, 0x29, 0x59, 0x29, 
	0x99, 0x21, 0x97, 0x21, 0xD9, 0x21, 0xD7, 0x21, 0xD5, 
	0x21, 0x93, 0x29, 0x91, 0x29, 0x95, 0x29, 0x99, 0x31, 
	0xDB, 0x29, 0x95, 0x21, 0x51, 0x21, 0xF, 0x21, 0xD, 
	0x29, 0xD, 0x20, 0xCD, 0x41, 0x57, 0x39, 0x97, 0x39, 
	0xD7, 0x39, 0x99, 0x39, 0x99, 0x49, 0x9B, 0x39, 0x17, 
	0x21, 0x11, 0x19, 0xD, 0x19, 0xD, 0x3B, 0x1D, 0x43, 
	0xA1, 0x4B, 0xE3, 0x31, 0x97, 0x21, 0x11, 0x21, 0x13, 
	0x21, 0x55, 0x21, 0x53, 0x21, 0x95, 0x21, 0x95, 0x21, 
	0x93, 0x21, 0x93, 0x21, 0x11, 0x29, 0x53, 0x21, 0x55, 
	0x19, 0x55, 0x21, 0x53, 0x21, 0x11, 0x18, 0xCF, 0x18, 
	0x89, 0x18, 0x49, 0x18, 0x4B, 0x31, 0x13, 0x31, 0x15, 
	0x31, 0x55, 0x31, 0x99, 0x29, 0x97, 0x31, 0x95, 0x29, 
	0x53, 0x29, 0x11, 0x21, 0xF, 0x10, 0xCB, 0x21, 0x51, 
	0x21, 0x93, 0x32, 0x57, 0x31, 0x53, 0x29, 0xF, 0x21, 
	0xF, 0x19, 0x11, 0x19, 0x11, 0x21, 0x53, 0x21, 0x51, 
	0x21, 0x51, 0x19, 0xF, 0x21, 0xF, 0x21, 0x11, 0x21, 
	0x11, 0x19, 0x11, 0x18, 0xCF, 0x18, 0xCF, 0x10, 0x8D, 
	0x10, 0x8B, 0x18, 0x8B, 0x18, 0x8D, 0x28, 0xD1, 0x31, 
	0x15, 0x29, 0x57, 0x21, 0x59, 0x21, 0x55, 0x21, 0x51, 
	0x21, 0xF, 0x21, 0x11, 0x21, 0x13, 0x18, 0xCF, 0x18, 
	0xCD, 0x21, 0x11, 0x29, 0x93, 0x31, 0x51, 0x20, 0x8D, 
	0x18, 0xCD, 0x19, 0xD, 0x19, 0xD, 0x19, 0xF, 0x19, 
	0xF, 0x19, 0xD, 0x19, 0xB, 0x10, 0xCB, 0x20, 0xCD, 
	0x20, 0xCF, 0x20, 0x8F, 0x18, 0x8D, 0x18, 0x8D, 0x18, 
	0xCD, 0x10, 0x8B, 0x10, 0x89, 0x18, 0x8D, 0x20, 0xD1, 
	0x31, 0x17, 0x31, 0x59, 0x21, 0x17, 0x19, 0x13, 0x11, 
	0xF, 0x19, 0xD, 0x21, 0x51, 0x29, 0x53, 0x21, 0x11, 
	0x19, 0xD, 0x19, 0xF, 0x29, 0x55, 0x31, 0xF, 0x18, 
	0x89, 0x18, 0x8B, 0x18, 0xCB, 0x18, 0xCB, 0x18, 0xCB, 
	0x10, 0xCB, 0x10, 0xC9, 0x10, 0xC9, 0x10, 0x89, 0x18, 
	0x8B, 0x20, 0x8D, 0x20, 0x8B, 0x18, 0x8B, 0x18, 0x8D, 
	0x10, 0xCB, 0x10, 0x89, 0x10, 0x89, 0x10, 0x8B, 0x18, 
	0x8F, 0x20, 0xD1, 0x28, 0xD5, 0x21, 0x11, 0x10, 0xCF, 
	0x11, 0xD, 0x19, 0xD, 0x21, 0xF, 0x29, 0x11, 0x21, 
	0xF, 0x19, 0xD, 0x19, 0x51, 0x31, 0x99, 0x30, 0xCF, 
	0x20, 0x89, 0x18, 0x89, 0x18, 0x89, 0x10, 0x89, 0x20, 
	0x8B, 0x18, 0x89, 0x10, 0x87, 0x10, 0x87, 0x10, 0x87, 
	0x18, 0x8B, 0x18, 0x8B, 0x10, 0x47, 0x10, 0x47, 0x10, 
	0x89, 0x10, 0x89, 0x10, 0x89, 0x10, 0x87, 0x10, 0x89, 
	0x21, 0xD, 0x18, 0x8D, 0x18, 0x8D, 0x20, 0xCF, 0x10, 
	0x8B, 0x10, 0xCB, 0x10, 0xCB, 0x18, 0xCB, 0x21, 0xD, 
	0x19, 0xD, 0x19, 0xF, 0x19, 0x95, 0x31, 0xDB, 0x29, 
	0xD, 0x18, 0x47, 0x18, 0x47, 0x10, 0x47, 0x10, 0x47, 
	0x18, 0x89, 0x18, 0x89, 0x10, 0x47, 0x10, 0x85, 0x10, 
	0x47, 0x18, 0x49, 0x10, 0x47, 0x8, 0x45, 0x8, 0x45, 
	0x10, 0x47, 0x10, 0x47, 0x18, 0x47, 0x10, 0x47, 0x10, 
	0x47, 0x10, 0x47, 0x10, 0x47, 0x10, 0x49, 0x18, 0x8D, 
	0x18, 0x8B, 0x10, 0x49, 0x18, 0x8B, 0x18, 0x8B, 0x18, 
	0xCB, 0x10, 0xCB, 0x11, 0xF, 0x19, 0x95, 0x29, 0xD9, 
	0x21, 0xB, 0x10, 0x45, 0x10, 0x45, 0x18, 0x87, 0x10, 
	0x47, 0x10, 0x47, 0x10, 0x47, 0x8, 0x45, 0x10, 0x87, 
	0x10, 0x87, 0x10, 0x89, 0x8, 0x47, 0x8, 0x45, 0x8, 
	0x45, 0x8, 0x3, 0x10, 0x45, 0x20, 0x49, 0x20, 0x49, 
	0x18, 0x47, 0x8, 0x5, 0x8, 0x45, 0x8, 0x47, 0x10, 
	0x49, 0x18, 0x49, 0x18, 0x49, 0x18, 0x4B, 0x10, 0x49, 
	0x10, 0x89, 0x10, 0xCB, 0x11, 0xD, 0x19, 0x11, 0x21, 
	0x95, 0x21, 0xB, 0x10, 0x87, 0x10, 0x47, 0x18, 0x47, 
	0x10, 0x47, 0x10, 0x47, 0x10, 0x47, 0x10, 0x45, 0x10, 
	0x45, 0x10, 0x47, 0x10, 0x47, 0x8, 0x47, 0x8, 0x45, 
	0x8, 0x5, 0x8, 0x3, 0x8, 0x3, 0x18, 0x7, 0x20, 
	0x49, 0x18, 0x47, 0x8, 0x45, 0x8, 0x45, 0x8, 0x47, 
	0x8, 0x47, 0x10, 0x49, 0x18, 0x49, 0x20, 0x4B, 0x18, 
	0x49, 0x10, 0x47, 0x10, 0x89, 0x10, 0x8B, 0x10, 0xCB, 
	0x21, 0x51, 0x21, 0xB, 0x18, 0x87, 0x18, 0x47, 0x18, 
	0x47, 0x10, 0x47, 0x10, 0x47, 0x10, 0x47, 0x8, 0x5, 
	0x8, 0x5, 0x10, 0x45, 0x10, 0x47, 0x8, 0x45, 0x8, 
	0x45, 0x0, 0x3, 0x0, 0x3, 0x8, 0x5, 0x18, 0x47, 
	0x20, 0x49, 0x18, 0x47, 0x8, 0x5, 0x8, 0x5, 0x8, 
	0x45, 0x8, 0x5, 0x10, 0x7, 0x18, 0x9, 0x20, 0x49, 
	0x18, 0x7, 0x8, 0x5, 0x8, 0x5, 0x8, 0x47, 0x8, 
	0x89, 0x18, 0xCD, 0x31, 0x4F, 0x28, 0xCD, 0x20, 0x8B, 
	0x18, 0x49, 0x10, 0x47, 0x10, 0x47, 0x8, 0x5, 0x8, 
	0x5, 0x10, 0x45, 0x10, 0x45, 0x10, 0x5, 0x10, 0x45, 
	0x8, 0x45, 0x8, 0x43, 0x8, 0x3, 0x10, 0x47, 0x18, 
	0x49, 0x20, 0x4B, 0x18, 0x49, 0x8, 0x47, 0x8, 0x45, 
	0x0, 0x3, 0x8, 0x45, 0x10, 0x45, 0x18, 0x47, 0x20, 
	0x9, 0x18, 0x7, 0x10, 0x5, 0x8, 0x5, 0x8, 0x45, 
	0x8, 0x47, 0x10, 0x89, 0x4A, 0x59, 0x41, 0xD5, 0x38, 
	0xCF, 0x28, 0xCD, 0x20, 0xC9, 0x18, 0xC9, 0x10, 0x89, 
	0x18, 0xC9, 0x18, 0x87, 0x18, 0x87, 0x18, 0x89, 0x18, 
	0x87, 0x18, 0x89, 0x18, 0x87, 0x18, 0x89, 0x20, 0xCB, 
	0x28, 0xCF, 0x28, 0xCF, 0x28, 0xCF, 0x18, 0xC9, 0x18, 
	0x87, 0x10, 0x87, 0x10, 0x87, 0x18, 0x87, 0x20, 0x89, 
	0x30, 0x8D, 0x30, 0x8D, 0x20, 0x89, 0x20, 0x89, 0x18, 
	0x89, 0x18, 0x87, 0x20, 0xCB, 
};

Vtx skybox_Cube_mesh_vtx_0[24] = {
	{{{213, 213, -213},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-213, 213, -213},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-213, 213, 213},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{213, 213, 213},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{213, -213, 213},0, {-16, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{213, 213, 213},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-213, 213, 213},0, {1008, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-213, -213, 213},0, {1008, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-213, -213, 213},0, {1008, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-213, 213, 213},0, {1008, -16},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-213, 213, -213},0, {-16, -16},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-213, -213, -213},0, {-16, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-213, -213, -213},0, {-16, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{213, -213, -213},0, {1008, 1008},{0x0, 0x81, 0x0, 0xFF}}},
	{{{213, -213, 213},0, {1008, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-213, -213, 213},0, {-16, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{213, -213, -213},0, {-16, -16},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{213, 213, -213},0, {-16, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{213, 213, 213},0, {1008, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{213, -213, 213},0, {1008, -16},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-213, -213, -213},0, {1008, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-213, 213, -213},0, {1008, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{213, 213, -213},0, {-16, -16},{0x0, 0x0, 0x81, 0xFF}}},
	{{{213, -213, -213},0, {-16, 1008},{0x0, 0x0, 0x81, 0xFF}}},
};

Gfx skybox_Cube_mesh_tri_0[] = {
	gsSPVertex(skybox_Cube_mesh_vtx_0 + 0, 16, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSP1Triangle(8, 9, 10, 0),
	gsSP1Triangle(8, 10, 11, 0),
	gsSP1Triangle(12, 13, 14, 0),
	gsSP1Triangle(12, 14, 15, 0),
	gsSPVertex(skybox_Cube_mesh_vtx_0 + 16, 8, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(4, 6, 7, 0),
	gsSPEndDisplayList(),
};


Gfx mat_skybox_sm64_material[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPClearGeometryMode(G_CULL_BACK),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, skybox_space_texture_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 124, 124),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPSetLights1(skybox_sm64_material_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_skybox_sm64_material[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_CULL_BACK),
	gsSPEndDisplayList(),
};


Gfx skybox_Cube_mesh[] = {
	gsSPDisplayList(mat_skybox_sm64_material),
	gsSPDisplayList(skybox_Cube_mesh_tri_0),
	gsSPDisplayList(mat_revert_skybox_sm64_material),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};


