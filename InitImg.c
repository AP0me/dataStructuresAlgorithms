#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
  uint16_t type;
  uint32_t size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset;
} BMPHeader;

typedef struct {
  uint32_t size;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bit_count;
  uint32_t compression;
  uint32_t size_image;
  int32_t x_pixels_per_meter;
  int32_t y_pixels_per_meter;
  uint32_t colors_used;
  uint32_t colors_important;
} BMPInfoHeader;
#pragma pack(pop)

int main(int argc, char *argv[]){
  const int N = atoi(argv[1]); // change this value for different image sizes
  const int width_in_bytes = ((N * 24 + 31) / 32) * 4;
  const int padding_size = width_in_bytes - (N * 3);

  BMPHeader header = {
    .type = 0x4d42,
    .size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + width_in_bytes * N + N * padding_size,
    .reserved1 = 0,
    .reserved2 = 0,
    .offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader)
  };

  BMPInfoHeader info_header = {
    .size = sizeof(BMPInfoHeader),
    .width = N,
    .height = N,
    .planes = 1,
    .bit_count = 24,
    .compression = 0,
    .size_image = 0,
    .x_pixels_per_meter = 0,
    .y_pixels_per_meter = 0,
    .colors_used = 0,
    .colors_important = 0
  };

  FILE *fp = fopen("./img/example.bmp", "wb");
  if (!fp) {
    perror("Could not open file");
    return 1;
  }

  fwrite(&header, sizeof(BMPHeader), 1, fp);
  fwrite(&info_header, sizeof(BMPInfoHeader), 1, fp);

  uint8_t white_pixel[3] = {255, 255, 255};
  uint8_t black_pixel[3] = {0, 0, 0};
  uint8_t padding[3] = {0, 0, 0};

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == 0 || j == 0 || i == N-1 || j == N-1) {
        fwrite(&black_pixel, sizeof(uint8_t), 3, fp);
      } else {
        fwrite(&white_pixel, sizeof(uint8_t), 3, fp);
      }
    }
    fwrite(&padding, sizeof(uint8_t), padding_size, fp);
  }

  fclose(fp);
  return 0;
}
