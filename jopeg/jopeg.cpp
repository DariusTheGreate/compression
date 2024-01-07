#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "stb_image.c"

typedef unsigned char uint8;
typedef unsigned int uint32;

//in case its possible to gain speed from it
void* jopeg_allocate(uint32 size){
    return malloc(size);
}

void jopeg_free(void* data){
    free(data);
}

//Unoptimised unsimded uncached garbage
struct DCT{
    const int w = 8;
    const int h = 8;
    const int num_of_compression_channels = 1;//now only Y space of YCbCr
    const float pi = 3.14;
    const uint32 quants[64] = { 16,11,12,14,12,10,16,14,13,14,18,17,16,19,24,40,26,24,22,22,24,49,35,37,29,40,58,51,61,60,57,51,56,55,64,72,92,78,64,68,87,69,55,56,80,109,81,87,95,98,103,104,103,62,77,113,121,112,100,120,92,101,103,99 };

    void dctTransform(float* matrix)
    {
        int i, j, k, l;
     
        float dct[h][w];
     
        float ci, cj, dct1, sum;
     
        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j++) {
                if (i == 0)
                    ci = 1 / sqrt(h);
                else
                    ci = sqrt(2) / sqrt(h);
                if (j == 0)
                    cj = 1 / sqrt(w);
                else
                    cj = sqrt(2) / sqrt(w);
     
                sum = 0;
                for (k = 0; k < h; k++) {
                    for (l = 0; l < w; l++) {
                        dct1 = matrix[l* 8 + k] *
                               cos((2 * k + 1) * i * pi / (2 * h)) *
                               cos((2 * l + 1) * j * pi / (2 * w));
                        sum = sum + dct1;
                    }
                }
                dct[i][j] = ci * cj * sum;
            }
        }
     
        for (i = 0; i < h; i++) {
            for (j = 0; j < w; j++) {
                matrix[i * h + j] = dct[j][i];
            }
        }
    }
    
    void quantize_dct(float* matrix){
        for(int y = 0; y < h; ++y){
            for(int x = 0; x < w; ++x){
                matrix[y * w + x] = floor(matrix[y * w + x] / quants[y * w + x]);
                if(abs(matrix[y * w + x]) < 2)
                    matrix[y * w + x] = 0;
            }
        }    
    }

}; 

class file_manager{
    FILE* fp;
public:
    file_manager(const std::string& filename) {
        fp = std::fopen(filename.c_str(), "wb"); 
        if(!fp){
            std::cout << "error opening file\n";
            exit(0);
        }
    }

    void write_data(uint8* data, uint32 size){
        if(!std::fwrite(data, size, 1, fp)){
            std::cout << "error writing file\n";
            exit(1);
        }
    }

    void write_byte(uint8 b){
        write_data(&b, sizeof(b));
    }

    ~file_manager(){
        if(fp && fclose(fp) != EOF){
            std::cout << "error closing file\n";
            exit(1);
        }
    }
};

struct rgb{
    uint8 r,g,b;
};

class image_channel{
    float* img_data;
    uint32 w, h;
public:
    image_channel(uint32 x, uint32 y) : w(x), h(y) {
       img_data = static_cast<float*>(jopeg_allocate(w * h * sizeof(float))); 
    }

    ~image_channel() {
        jopeg_free(img_data);
    }

    void set(float pixel, uint32 x, uint32 y){
        img_data[y * w + x] = pixel; 
    }

    float get(uint32 x, uint32 y) const {
        return img_data[y * w + x];
    }

    uint32 get_w() const {
        return w;
    }
    
    uint32 get_h() const {
        return h;
    }
    
    void print_myself() const {
        for(uint32 y = 0; y < get_h(); ++y){
            for(uint32 x = 0; x < get_w(); ++x){
                std::cout << get(x,y) << " ";
            }
            std::cout << "\n"; 
        }
    }

    void crop_image(float* sample, uint32 x, uint32 y){
        if(x + 8 > w || y + 8 > h)
            return;
        for(uint32 j = y; j < y + 8; ++j){
            for(uint32 i = x; i < x + 8; ++i){
                sample[((j - y) * 8) + (i-x)] = get(i, j);
            }
        }
    }
};

class JOPEG{
    uint32 MCUx, MCUy;

    int H, W;
    int number_of_channels;

public:
    JOPEG(const char* filename){
        uint8* img_data = stbi_load(filename, &W, &H, &number_of_channels, 3);
        if(!img_data){
            std::cout << "can't load img\n";
            exit(1);
        }

        image_channel Ychannel(W,H);    

        for(int y = 0; y < H; ++y){
            for (int x = 0; x < W; x++) {
                rgb* data = (rgb*)img_data;
                Ychannel.set((data[y * W + x].r*0.299) + (data[y * W + x].g*0.587) + (data[y * W + x].b*0.114) - 128, x, y);
            }
        }
        
        std::cout << Ychannel.get_w() << " " << Ychannel.get_h() << "\n"; 
        Ychannel.print_myself(); 
        std::cout << "*******##########*******\n";

        int iternum = 0;
        for(int y = 0; y < H; y+=8){
            for(int x = 0; x < W; x+=8){
                float sample[64] = {0};                            
                iternum++;
                std::cout << "iter_num: " << iternum << "\n";
                Ychannel.crop_image(sample, x, y);

                for(int i = 0; i < 64; ++i)
                {
                    std::cout << sample[i] << " ";
                    if((i+1)%8 == 0)
                        std::cout << "\n";
                }

                std::cout << "------------------------\n";
                DCT().dctTransform(sample);
                DCT().quantize_dct(sample);

                for(int i = 0; i < 64; ++i)
                {
                    std::cout << sample[i] << " ";
                    if((i+1)%8 == 0)
                        std::cout << "\n";
                }
                std::cout << "\n";
            } 
        }
    }
};

int main(){
    JOPEG j("test2.png");
    return 0;
}
