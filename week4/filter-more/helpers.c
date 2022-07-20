#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avergb = (int) round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            //设置成整数
            image[i][j].rgbtRed = avergb;
            image[i][j].rgbtGreen = avergb;
            image[i][j].rgbtBlue = avergb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = width - 1; j >= 0; j--) //注意这里width-1 j是大于等于0
        {
            pixel[i][width - 1 - j] = image[i][j];
            //pixel必须要从[0][0]开始定义，不能从第一行的最右侧开始定义
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = pixel[i][j];
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*pseudocode
    for each row
    for each col
        set count to 0
        for every neighboring pixel within the radius m in the x direction
            for every neighboring pixel within the radius m in the y direction
                 add the color to the total
                 count++
        final_color = total/count
        setpixel(current x, current y, final_color)
    */
    RGBTRIPLE temp[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int count = 0;
            int rowCoords[] = { row - 1, row, row + 1 }; //注意这里是逗号
            int colCoords[] = { col - 1, col, col + 1 };
            float totalR = 0, totalG = 0, totalB = 0; //三个需要分开写
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int curRow = rowCoords[r]; //注意这里要申明变量类型
                    int curCol = colCoords[c];
                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width) //只考虑大于0的
                    {
                        RGBTRIPLE pixel = image[curRow][curCol]; //先把image上该位置的值赋予pixel
                        totalR += pixel.rgbtRed; //在用pixel位置上的值计算
                        totalG += pixel.rgbtGreen;
                        totalB += pixel.rgbtBlue;
                        count ++; //每加一个格子，count加1，最后求平均
                    }
                }
            }
            temp[row][col].rgbtRed = round(totalR / count);
            temp[row][col].rgbtGreen = round(totalG / count);
            temp[row][col].rgbtBlue = round(totalB / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /*pseudocode
    设置两个矩阵Gx Gy
    提取每一个点
        每一个点乘以矩阵Gx 分别存储三个值
            注意边缘的点(超过边界的都是0)
        每一个点乘以矩阵Gy 分别存储三个值
            注意边缘的点(超过边界的都是0)
        平方和开方(gx^2 + gy^2)^(1/2)
            注意值不能超过255 以及必须是正数
        赋值到temp中
    temp最后赋值到image中
    */

    //注意生成矩阵的格式
    int Gx[3][3] =
    {
        { -1, 0, 1 },
        { -2, 0, 2 },
        { -1, 0, 1 }
    };
    int Gy[3][3] =
    {
        { -1, -2, -1 },
        { 0, 0, 0 },
        { 1, 2, 1 }
    };

    RGBTRIPLE temp[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int rowCoords[] = { row - 1, row, row + 1 };
            int colCoords[] = { col - 1, col, col + 1 };
            float totalxR = 0, totalxG = 0, totalxB = 0;
            float totalyR = 0, totalyG = 0, totalyB = 0;
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int curRow = rowCoords[r]; //注意这里要申明变量类型
                    int curCol = colCoords[c];
                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        RGBTRIPLE pixel = image[curRow][curCol]; //先把image上该位置的值赋予pixel
                        totalxR += pixel.rgbtRed * Gx[r][c]; //在用pixel位置上的值*Gx[0~2][0~2] //注意这里不是curRow和curCol
                        totalxG += pixel.rgbtGreen * Gx[r][c];
                        totalxB += pixel.rgbtBlue * Gx[r][c];
                        totalyR += pixel.rgbtRed * Gy[r][c]; //在用pixel位置上的值计算
                        totalyG += pixel.rgbtGreen * Gy[r][c];
                        totalyB += pixel.rgbtBlue * Gy[r][c];
                    }
                }
            }
            int finalR = round(sqrt(totalxR * totalxR + totalyR * totalyR));
            int finalG = round(sqrt(totalxG * totalxG + totalyG * totalyG));
            int finalB = round(sqrt(totalxB * totalxB + totalyB * totalyB));
            temp[row][col].rgbtRed = finalR > 255 ? 255 : finalR; //如果大于255，就把255赋值给finalR
            temp[row][col].rgbtGreen = finalG > 255 ? 255 : finalG;
            temp[row][col].rgbtBlue = finalB > 255 ? 255 : finalB;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

/*guidance
    https://www.youtube.com/watch?v=XeAZtdrSi0Q
*/
