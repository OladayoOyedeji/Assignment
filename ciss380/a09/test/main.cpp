#include <iostream>
#include <cmath>

const int n = 2;
const int N = pow(2, n) + 1;
const float M = 0.25 * N;

float heightmap[N][N] = {};

void diamond_average(float heightmap[N][N], int midy, int midx, int w, int start, int end)
{
    float sum = 0;
    int n = 0;

    if (midx - w/2 >= start && midy >= start &&
        midx - w/2 < end    && midy < end)
    {
        sum += heightmap[midx-w/2][midy];
        n += 1;
    }
    if (midx + w/2 >= start && midy >= start &&
        midx + w/2 < end    && midy < end)
    {
        sum += heightmap[midx+w/2][midy];
        n += 1;
    }
    if (midx >= start && midy + w/2 >= start &&
        midx < end    && midy + w/2 < end)
    {
        sum += heightmap[midx][midy+w/2];
        n += 1;
    }
    if (midx >= start && midy - w/2 >= start &&
        midx < end    && midy - w/2 < end)
    {
        sum += heightmap[midx][midy-w/2];
        n += 1;
    }
    //std::cout << "n: " << n << std::endl;
    if (n == 0) return;

    heightmap[midx][midy] = sum / n;// + float(rand()) / RAND_MAX * 2 * M - M;
}

void DIAMOND_SQAURE_algorithm(float heightmap[N][N], float M, float roughness, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            heightmap[i][j] = 0;
        }
    }
    heightmap[0][0] = float(rand()) / RAND_MAX * 2 * M - M ;
    heightmap[0][N-1] = float(rand()) / RAND_MAX * 2 * M - M ;
    heightmap[N-1][0] = float(rand()) / RAND_MAX * 2 * M - M ;
    heightmap[N-1][N-1] = float(rand()) / RAND_MAX * 2 * M - M  ;

    for (int width = N-1; width != 1; width/=2)
    {
        for (int r = 0; r < N; ++r)
        {
            for (int c = 0; c < N; ++c)
            {
                std::cout << heightmap[r][c] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << std::endl;
        // diamond step
        for (int h = 0; h < N - 1; h += width)
        {
            for (int w = 0; w < N - 1; w += width)
            {
                std::cout << h << ' ' << w << ' ' << width << std::endl;;
                heightmap[h + width / 2][w + width /2] = (heightmap[h][w] + heightmap[h + width][w] +
                                                          heightmap[h][w + width] + heightmap[h + width][w + width]) / 4;//+
                //float(rand()) / RAND_MAX * 2 * M - M;
/* +
   float(rand()) / RAND_MAX * 2 * M - M;*/
            }
        }

        for (int r = 0; r < N; ++r)
        {
            for (int c = 0; c < N; ++c)
            {
                std::cout << heightmap[r][c] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << std::endl;
        for (int h = 0; h < N-1; h += width)
        {
            for (int w = 0; w < N-1; w += width)
            {
                diamond_average(heightmap, h + width/2, w, width, 0, N);
                for (int r = 0; r < N; ++r)
                {
                    for (int c = 0; c < N; ++c)
                    {
                        std::cout << heightmap[r][c] << ' ';
                    }
                    std::cout << '\n';
                }
                std::cout << std::endl;
                diamond_average(heightmap, h, w + width/2, width, 0, N);
                for (int r = 0; r < N; ++r)
                {
                    for (int c = 0; c < N; ++c)
                    {
                        std::cout << heightmap[r][c] << ' ';
                    }
                    std::cout << '\n';
                }
                std::cout << std::endl;
                diamond_average(heightmap, h + width, w + width/2, width, 0, N);
                for (int r = 0; r < N; ++r)
                {
                    for (int c = 0; c < N; ++c)
                    {
                        std::cout << heightmap[r][c] << ' ';
                    }
                    std::cout << '\n';
                }
                std::cout << std::endl;
                diamond_average(heightmap, h + width / 2, w + width, width, 0, N);
            }
        }

        M *= pow(2, -roughness);
        std::cout << M << std::endl;
    }
    // for (int r = 0; r < N; ++r)
    // {
    //     for (int c = 0; c < N; ++c)
    //     {
    //         std::cout << heightmap[r][c] << ' ';
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << std::endl;
}

int main()
{

    

    DIAMOND_SQAURE_algorithm(heightmap, N * 0.25, 1.5, N);
    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            std::cout << heightmap[r][c] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
    
    return 0;
    
}
