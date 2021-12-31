#include<stdio.h>
#include<stdlib.h>

void readImage()
{
	FILE* fp = fopen("image-color.bmp", "rb");   //read the file//

	unsigned char imageHeader[54]; // to store the image header
	unsigned char colorTable[1024]; // to store the colorTable, if it exists

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

	// extract image height and width from imageHeader      
	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

	int imgDataSize = width * height; // calculate image size
	unsigned char buffer[imgDataSize];

	fread(buffer,sizeof(unsigned char),imgDataSize,fp);			//read image data

	fclose(fp);   //reading image successful
}

void writeImage()
{
	FILE* fp = fopen("image-color.bmp", "rb");   //read the file//

	unsigned char imageHeader[54]; // to store the image header
	unsigned char colorTable[1024]; // to store the colorTable, if it exists

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

	FILE *fo = fopen("testing-image-write.bmp", "wb");

	fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back

	// extract image height and width from imageHeader      
	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

	if(bitDepth <= 8)	// COLOR TABLE Present
       		fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

	int imgDataSize = width * height; // calculate image size
	unsigned char buffer[imgDataSize];

	fread(buffer, sizeof(unsigned char), imgDataSize, fp);			//read image data

	fwrite( buffer, sizeof(unsigned char), imgDataSize, fo); // write the values of the black & white image.

	fclose(fo);
	fclose(fp);
}

void extractImageData()
{
	FILE* fp = fopen("image-color.bmp", "rb");   //read the file//

	unsigned char imageHeader[54]; // to store the image header
	unsigned char colorTable[1024]; // to store the colorTable, if it exists

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

	// extract image height and width from imageHeader      
	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

	int imgDataSize = width * height; // calculate image size
	unsigned char buffer[imgDataSize];

	fread(buffer,sizeof(unsigned char),imgDataSize,fp);			//read image data
	//extraction of DATA successful

	printf("The resolution of image is width x height = %d x %d\n",width,height);

	fclose(fp);
}

void outputPixelValue()
{
	int i,r,c;
	FILE* fp = fopen("image-color.bmp","r");   //read the image file
	unsigned char header[54]; // to store the image header

	for(i=0;i<54;i++)
		header[i] = getc(fp);  // strip out BMP header, byte-wise

	int width = *(int*)&header[18]; // read the width from the image header
	int height = *(int*)&header[22]; // read the height from the image header

	unsigned char buf[height * width]; // to store the image data

	fread(buf, sizeof(unsigned char), (height * width), fp);

	printf("Enter the row and column value to obtain the pixel value\n");
	printf("ROW - ");scanf("%d",&r);    //row<height
	printf("COL - ");scanf("%d",&c);    //col<width

	i=( ( r - 1 ) * width) + c - 1;
	printf("\nThe pixel value at (%d, %d) is - %d",r,c,buf[i]);

	fclose(fp);
}

void changePixelValue()
{
	int i,r,c,p;
	FILE* fp = fopen("image-color.bmp","r");   //read the image file
	unsigned char header[54]; // to store the image header

	for(i=0;i<54;i++)
		header[i] = getc(fp);  // strip out BMP header, byte-wise

	int width = *(int*)&header[18]; // read the width from the image header
	int height = *(int*)&header[22]; // read the height from the image header

	unsigned char buf[height * width]; // to store the image data

	fread(buf, sizeof(unsigned char), (height * width), fp);

	printf("Enter the row and column value to change the pixel value\n");
	printf("ROW - ");scanf("%d",&r);    //row<height
	printf("COL - ");scanf("%d",&c);    //col<width
	printf("Enter the new pixel value - ");scanf("%d",&p);
	
	i=( ( r - 1 ) * width) + c - 1;
	buf[i]=p;

	fclose(fp);

}

void convertToGray()
{
	int i,y;

	FILE* fp = fopen("image-color.bmp", "rb");   //read the file//

	unsigned char imageHeader[54]; // to store the image header
	unsigned char colorTable[1024]; // to store the colorTable, if it exists

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

	// extract image height and width from imageHeader      
	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

	FILE *fo = fopen("image-gray.bmp", "wb");

	fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back.
	if(bitDepth <= 8)       			    // COLOR TABLE Present
	        fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

	int imgDataSize = width * height;		//calculate image size
	unsigned char buffer[imgDataSize][3];   		
	    buffer[i][2] = getc(fp);                   //blue
	    buffer[i][1] = getc(fp);                   //green
	    buffer[i][0] = getc(fp);                   //red

	for(i=0;i<imgDataSize;i++)
	{
	    y = 0;
	    buffer[i][2] = getc(fp);					//blue
	    buffer[i][1] = getc(fp);					//green
	    buffer[i][0] = getc(fp);					//red
			
	    y = (buffer[i][0]*0.3) + (buffer[i][1]*0.59) + (buffer[i][2]*0.11); //conversion formula of rgb to gray
	
	    putc(y,fo);
	    putc(y,fo);
	    putc(y,fo);
	}
	
	fclose(fo);
	fclose(fp);
}

void convertToBinary()
{
	int i;

	FILE* fp = fopen("image-color.bmp", "rb");   //read the file//

	unsigned char imageHeader[54]; // to store the image header
	unsigned char colorTable[1024]; // to store the colorTable, if it exists

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

	// extract image height and width from imageHeader      
	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

	int imgDataSize = width * height; // calculate image size
	unsigned char buffer[imgDataSize];

	fread(buffer,sizeof(unsigned char),imgDataSize,fp);			//read image data

	for(i = 0; i < imgDataSize; i++)
	{
		buffer[i] = (buffer[i] > 128) ? 255 : 0;
	}

	FILE *fo = fopen("image-binary.bmp", "wb");

	fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back

	if(bitDepth <= 8)	// COLOR TABLE Present
       		fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

	fwrite( buffer, sizeof(unsigned char), imgDataSize, fo); // write the values of the black & white image.

	fclose(fo);
	fclose(fp);
}

void crop()
{
	int i,r1,r3;

	FILE* fp = fopen("image-color.bmp", "rb");   //read the file//

	unsigned char imageHeader[54]; // to store the image header
	unsigned char colorTable[1024]; // to store the colorTable, if it exists

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

	// extract image height and width from imageHeader      
	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

	int imgDataSize = width * height; // calculate image size
	unsigned char buffer[imgDataSize];

	fread(buffer,sizeof(unsigned char),imgDataSize,fp);			//read image data

	printf("Enter the upper ROW value :-\n");
	printf("ROW - ");scanf("%d",&r1);

	printf("Enter the lower ROW value :-\n");
	printf("ROW - ");scanf("%d",&r3);

	for(i=0;i<(r1-1)*width;i++)
		buffer[i]=0;
	for(i=r3*width;i<imgDataSize;i++)
		buffer[i]=0;

	FILE *fo = fopen("image-crop.bmp", "wb");

	fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back

	if(bitDepth <= 8)	// COLOR TABLE Present
       		fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

	fwrite( buffer, sizeof(unsigned char), imgDataSize, fo); // write the values of the black & white image.

	fclose(fo);
	fclose(fp);
}

void flip_Vertical()
{
	int i,j;

	FILE* fp = fopen("image-color.bmp", "rb");   //read the file//

	unsigned char imageHeader[54]; // to store the image header
	unsigned char colorTable[1024]; // to store the colorTable, if it exists

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

	// extract image height and width from imageHeader      
	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

	int imgDataSize = width * height; // calculate image size
	unsigned char buffer[imgDataSize];

	fread(buffer,sizeof(unsigned char),imgDataSize,fp);			//read image data

	unsigned char buffer_v[imgDataSize];

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			buffer_v[i*width+j]=buffer[i*width+width-j];
		}
	}

	FILE *fo = fopen("image-flip-vertical.bmp", "wb");

	fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back

	if(bitDepth <= 8)	// COLOR TABLE Present
       		fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

	fwrite( buffer_v, sizeof(unsigned char), imgDataSize, fo); // write the values of the black & white image.

	fclose(fo);
	fclose(fp);
}

void flip_Horizontal()
{
	int i,j;

	FILE* fp = fopen("image-color.bmp", "rb");   //read the file//

	unsigned char imageHeader[54]; // to store the image header
	unsigned char colorTable[1024]; // to store the colorTable, if it exists

	fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

	// extract image height and width from imageHeader      
	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	if(bitDepth <= 8)	// COLOR TABLE Present
		fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

	int imgDataSize = width * height; // calculate image size
	unsigned char buffer[imgDataSize];

	fread(buffer,sizeof(unsigned char),imgDataSize,fp);			//read image data

	unsigned char buffer_h[imgDataSize];

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			buffer_h[i*width+j]=buffer[(height-i)*width+width-j];
		}
	}

	FILE *fo = fopen("image-flip-horizontal.bmp", "wb");

	fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back

	if(bitDepth <= 8)	// COLOR TABLE Present
       		fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

	fwrite( buffer_h, sizeof(unsigned char), imgDataSize, fo); // write the values of the black & white image.

	fclose(fo);
	fclose(fp);
}

main()
{
	int a,x=1;
	while(x!=0)
	{
	printf("Enter 0 to EXIT, 1 to Read an Image into Array, 2 to Write an Image into Array, 3 to Extract Image Data, 4 to Get Pixel Value at particular (r,c), 5 to Change Pixel Value at particular (r,c), 6 to Convert to GRAY, 7 to Convert to BINARY, 8 to Crop Image, 9 to Flip through Vertical Line, 10 to Flip through Horizontal Line\n\n");
	scanf("%d",&a);
	switch(a)
	{
		case 0:
			x=0;
			printf("\n***\tTERMINATED\t***\n\n");
		break;
		case 1:
			readImage();
			printf("\nImage Reading is successful.\n\n");
		break;
		case 2:
			writeImage();
			printf("\nImage Writing is successful.\n\n");
		break;
		case 3:
			extractImageData();
			printf("\nImage Data Extracting is successful.\n\n");
		break;
		case 4:
			outputPixelValue();
			printf("\n\nOutput of pixel value is successful.\n\n");
		break;
		case 5:
			changePixelValue();
			printf("\nChange of pixel value is successful.\n\n");
		break;
		case 6:
			convertToGray();
			printf("\nImage Conversion to GrayScale successful.\n\n");
		break;
		case 7:
			convertToBinary();
			printf("\nImage Conversion to Binary successful.\n\n");
		break;
		case 8:
			crop();
			printf("\nImage Croping successful.\n\n");
		break;
		case 9:
			flip_Vertical();
			printf("\nImage Fliping successful.\n\n");
		break;
		case 10:
			flip_Horizontal();
			printf("\nImage Fliping successful.\n\n");
		break;
		default:
			printf("Enter a valid case...\n\n");
	}
	}
}
