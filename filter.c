/* A program to perform image convolutions on a .BMP image file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pixel {
    unsigned char r, g, b;
} Pixel;

typedef struct image {
    unsigned int width, height, max;
    Pixel **data;
} Image;

Image *readPPM(char *file_name){

    FILE *file = fopen(file_name, "r"); 
    if (!file){ //File could not be opened
        fprintf(stderr, "Unable to open file \"%s\"\n", file_name);
        return NULL;
    }

    char format[3];
    fscanf(file, "%s\n", format);
    if(strcmp(format, "P3")){ //P3 is a colour image
        return NULL;
    }
    
    Image *image = malloc(sizeof(Image));
    
    if(fscanf(file, "%u %u %u", &image->width, &image->height, &image->max) != 3){ //Since fscanf returns how many vars were scanned
        return NULL;
    }

    image->data = malloc(sizeof(Pixel *) * image->height);  
    
    for(int i = 0; i < image->height; i++){
        image->data[i] = malloc(sizeof(Pixel) * image->width);
    }
    
    for(int i = 0; i < image->height; i++){
        for(int j = 0; j < image->width; j++){
            int pixels_read = fscanf(file, "%hhu %hhu %hhu", &image->data[i][j].r, &image->data[i][j].g, &image->data[i][j].b);
            if(pixels_read != 3){
                return NULL;
            }
        }
    }
    
    fclose(file);
    
    return image;

}

int writePPM(char *file_name, Image *image){

    FILE *file = fopen(file_name, "w");
    if (!file){
        fprintf(stderr, "Unable to open file \"%s\"\n", file_name);
        return -1;
    }

    fprintf(file, "P3\n");
    fprintf(file, "%u %u\n", image->width, image->height);
    fprintf(file, "%u\n", image->max);

    for (int i = 0; i < image->height; i++){
        for (int j = 0; j < image->width; j++){
            fprintf(file, "%d %d %d ", image->data[i][j].r, image->data[i][j].g, image->data[i][j].b);
        }
        fprintf(file, "\n");
    }    

    fclose(file);
    return 0;
}

int main(int argc, char** argv){
    if(argc != 4){
        printf("%s\n","Incorrect args.");
        return -1;
    }
    
    /* READ KERNEL */
    FILE *kernel_reader = fopen(argv[2],"r");
    int n, scale;
    fscanf(kernel_reader,"%d %d",&n,&scale);

    int filter[n][n];

    for(int i = 0; i < n;i++){
        fscanf(kernel_reader,"%d %d %d", &filter[i][0], &filter[i][1], &filter[i][2]);
    }
    fclose(kernel_reader);
    /* FILTER */
    Image* image = readPPM(argv[1]);
    Image* output_image = readPPM(argv[1]);
    
    int h = n/2;
    int sum_r, sum_g, sum_b,Cx,Cy;

    for (int i = 0; i < image->height; i++){
        for (int j = 0; j < image->width; j++){
            sum_r = 0;
            sum_g = 0;
            sum_b = 0;
            
            for(int x = 0; x < n; x++){
                for(int y = 0; y < n; y++){
                    Cx = i + x - h;
                    Cy = j + y - h;
                    if((Cx >= 0 && Cx < image->height) && (Cy >= 0 && Cy < image->width)){
                        sum_r += image->data[Cx][Cy].r*filter[x][y];
                        sum_g += image->data[Cx][Cy].g*filter[x][y];
                        sum_b += image->data[Cx][Cy].b*filter[x][y];
                    }
                }
            }


            sum_r /= scale;
            sum_g /= scale;
            sum_b /= scale;

            if(sum_r < 0) sum_r = 0;
            if(sum_g < 0) sum_g = 0;
            if(sum_b < 0) sum_b = 0;

            if(sum_r > 255) sum_r = 255;
            if(sum_g > 255) sum_g = 255;
            if(sum_b > 255) sum_b = 255;
            output_image->data[i][j].r = sum_r;
            output_image->data[i][j].g = sum_g;
            output_image->data[i][j].b = sum_b;
        }
    }

    writePPM(argv[3],output_image);    
}


