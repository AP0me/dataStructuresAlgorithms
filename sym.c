//sym [-ahsv] [-seed number] [-o name] [-n number] [-size number]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BMP_HEADER_SIZE 14
#define BMP_INFOHEADER_SIZE 40

int readBMP(
  const char *out_filename, int seed, int height, int width, int bytes_per_pixel, int padding,
  unsigned char pixel_data[height][width * bytes_per_pixel + padding],
  unsigned char header[BMP_HEADER_SIZE], unsigned char info_header[BMP_INFOHEADER_SIZE], int outFType
  ){
  //set limit where line ends depending on line type.
  int limitWidth;
  if(outFType==0){ limitWidth=width-2; }
  else if(outFType==1){ limitWidth=width-2;  }
  else if(outFType==2){ limitWidth=width/2-1;}
  else if(outFType==3){ limitWidth=height-2; }
  else if(outFType==4){ limitWidth=width*3;  }

  //initialise different variables that will be accessable across this function.
  int modMem[2*limitWidth+1][3]; int memCord[2*limitWidth+1][2]; int modMemDim1=0;
  int x=0; int y=0; srand(seed); int random; int tobeAdded; int tempCord74; int desDirection=-1;

  //desDirection determines direction of line when -a or -s options are used. It is random with 50%-50% chance.
  if((outFType==0)||(outFType==2)){ desDirection = rand()%2; }
  //if (-a or -s with vertical desDirection) or -v is set.
  if((outFType==3)||(desDirection==1)){
    //Set strating position. TODO: might be incorrect range for x.
    x=(rand()%(width/2)-(width/4))+width/2;
    for(int i=0; i<limitWidth; i++){
      random = rand();
      tobeAdded = random%3-1; //Generate random integer between -1 and 1.
      y=y+1; x=x+tobeAdded;   //Add the random integer to x.
      if(x>width){ x=width; } if(x<0){ x=0; }//Protections.

      //Momorize replaced pixels.
      modMem[modMemDim1][0] = pixel_data[y][x * bytes_per_pixel + 0];
      modMem[modMemDim1][1] = pixel_data[y][x * bytes_per_pixel + 1];
      modMem[modMemDim1][2] = pixel_data[y][x * bytes_per_pixel + 2];
      memCord[modMemDim1][0]=y; memCord[modMemDim1][1]=x; modMemDim1++;
      
      //Modify the pixel at position (x, y)
      pixel_data[y][x * bytes_per_pixel + 0] = 0  ; //Blue channel
      pixel_data[y][x * bytes_per_pixel + 1] = 0  ; //Green channel
      pixel_data[y][x * bytes_per_pixel + 2] = 255; //Red channel
    }
  }
  else{
    //Set strating position. TODO: might be incorrect range for y.
    y=(rand()%(height/2)-(height/4))+height/2;
    for(int i=0; i<limitWidth; i++){
      random = rand();
      tobeAdded = random%3-1; //Generate random integer between -1 and 1.
      x=x+1; y=y+tobeAdded;   //Add the random integer to y.
      if(y>height){ y=height; } if(y<0){ y=0; }//Protections.

      //Momorize replaced pixels.
      modMem[modMemDim1][0] = pixel_data[y][x * bytes_per_pixel + 0];
      modMem[modMemDim1][1] = pixel_data[y][x * bytes_per_pixel + 1];
      modMem[modMemDim1][2] = pixel_data[y][x * bytes_per_pixel + 2];
      memCord[modMemDim1][0]=y; memCord[modMemDim1][1]=x; modMemDim1++;

      //Modify the pixel at position (x, y) of color table.
      pixel_data[y][x * bytes_per_pixel + 0] = 0  ; //Blue channel
      pixel_data[y][x * bytes_per_pixel + 1] = 0  ; //Green channel
      pixel_data[y][x * bytes_per_pixel + 2] = 255; //Red channel
    }
  }

  //For symmetric lines, mirror then draw the memoried pixels to color table for both directions.
  if(outFType==2){
    if(desDirection==1){
      for(int i=0; i<limitWidth; i++){
        pixel_data[height-1-memCord[i][0]][memCord[i][1] * bytes_per_pixel + 0] = 0; // blue channel
        pixel_data[height-1-memCord[i][0]][memCord[i][1] * bytes_per_pixel + 1] = 0; // green channel
        pixel_data[height-1-memCord[i][0]][memCord[i][1] * bytes_per_pixel + 2] = 255; // red channel
      }
    }
    else{
      for(int i=0; i<limitWidth; i++){
        pixel_data[memCord[i][0]][(width-1)*3-memCord[i][1] * bytes_per_pixel + 0] = 0; // blue channel
        pixel_data[memCord[i][0]][(width-1)*3-memCord[i][1] * bytes_per_pixel + 1] = 0; // green channel
        pixel_data[memCord[i][0]][(width-1)*3-memCord[i][1] * bytes_per_pixel + 2] = 255; // red channel
      }
    }

  }

  // open the output file for writing
  FILE *out_fp = fopen(out_filename, "wb");
  if (out_fp == NULL) {
    fprintf(stderr, "Error: could not open file '%s' for writing\n", out_filename);
    fclose(out_fp);
    return -1;
  }
  // write the header and info header to the output file
  fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, out_fp);
  fwrite(info_header, sizeof(unsigned char), BMP_INFOHEADER_SIZE, out_fp);
  // write the modified pixel data to the output file
  fwrite(pixel_data, sizeof(unsigned char), height * (width * bytes_per_pixel + padding), out_fp);
  fclose(out_fp);

  //Return back the replaced pixels for next iterations.
  int i;
  for(i=0; i<limitWidth; i++){
    pixel_data[memCord[i][0]][memCord[i][1] * bytes_per_pixel + 0] = modMem[i][0]; // blue channel
    pixel_data[memCord[i][0]][memCord[i][1] * bytes_per_pixel + 1] = modMem[i][1]; // green channel
    pixel_data[memCord[i][0]][memCord[i][1] * bytes_per_pixel + 2] = modMem[i][2]; // red channel
    if(outFType==2){
      if(desDirection==1){
        for(int i=0; i<limitWidth; i++){
          pixel_data[height-1-memCord[i][0]][memCord[i][1] * bytes_per_pixel + 0] = modMem[modMemDim1-i-1][0]; // blue channel
          pixel_data[height-1-memCord[i][0]][memCord[i][1] * bytes_per_pixel + 1] = modMem[modMemDim1-i-1][1]; // green channel
          pixel_data[height-1-memCord[i][0]][memCord[i][1] * bytes_per_pixel + 2] = modMem[modMemDim1-i-1][2]; // red channel
        }
      }
      else{
        for(int i=0; i<limitWidth; i++){
          pixel_data[memCord[i][0]][(width-1)*3-memCord[i][1] * bytes_per_pixel + 0] = modMem[modMemDim1-i-1][0]; // blue channel
          pixel_data[memCord[i][0]][(width-1)*3-memCord[i][1] * bytes_per_pixel + 1] = modMem[modMemDim1-i-1][1]; // green channel
          pixel_data[memCord[i][0]][(width-1)*3-memCord[i][1] * bytes_per_pixel + 2] = modMem[modMemDim1-i-1][2]; // red channel
        }
      }
    }
  }
  return random;
}

int main(int argc, char *argv[]) {
  //upon incorrect delivery of arguments print correct usage.
  if(argc!=5){ printf("Usage: sym [-ahsv] [-seed number] [-o name] [-n number]"); return -1; }
  //try to open pregenerated template image.
  char* filename = "./img/example.bmp";
  FILE *fp = fopen(filename, "rb");
  if (fp == NULL) { fprintf(stderr, "Error: could not open file '%s'\n", filename); return 0; }

  //read headers.
  unsigned char header[BMP_HEADER_SIZE];
  fread(header, sizeof(unsigned char), BMP_HEADER_SIZE, fp);
  int offset = *(int*)&header[10];
  unsigned char info_header[BMP_INFOHEADER_SIZE];
  fread(info_header, sizeof(unsigned char), BMP_INFOHEADER_SIZE, fp);

  //get image properties from header.
  int width = *(int*)&info_header[4];
  int height = *(int*)&info_header[8];
  int bit_depth = *(int*)&info_header[14];
  int bytes_per_pixel = bit_depth / 8;
  int padding = (4 - (width * bytes_per_pixel) % 4) % 4;
  //read the color table.
  unsigned char pixel_data[height][width * bytes_per_pixel + padding];
  fread(pixel_data, sizeof(unsigned char), height * (width * bytes_per_pixel + padding), fp);
  fclose(fp);

  //read configuration for type of line to be drawn.
  int outFType=1;
  switch(argv[1][1]){
    case 'a':
      outFType=0; break;
    case 'h':
      outFType=1; break;
    case 's':
      outFType=2; break;
    case 'v':
      outFType=3; break;
    default:
      outFType=4; break;
  }
  printf("output type %d\n", outFType);

  //read initial seed value and parce it to integer.
  char *seed = argv[2]; int initSeed; int tempHeight49;
  if(argv[2] == NULL){ initSeed = (int)time(NULL); }
  else{ initSeed = atoi(seed); }
  int nextSeed = initSeed; char outputFiles[20];
  printf("initial seed: %d\n", initSeed);

  //read number of outputs and their name.
  int outFileNumber = atoi(argv[4]);
  printf("number of outputs: %d\n", outFileNumber);
  char outname[100];
  strcpy(outname, argv[3]);
  printf("output file name: %s[N].bmp\n", outname);

  //create outputs according to given configurations.
  for(int i=0; i<outFileNumber; i++){
    sprintf(outputFiles, "./out/%s%d.bmp", outname, i);
    nextSeed = readBMP(
      outputFiles, nextSeed, height, width, bytes_per_pixel, padding,
      pixel_data, header, info_header, outFType
    );
  }
  printf("finished\n");
  return 0;
}
