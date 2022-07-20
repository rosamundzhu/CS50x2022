#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool cycle(int loser, int winner); //判断是否是circle

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false; //先都初始化为false
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        // ranks[i] is the index of the candidate who is the ith preference for the voter.
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) //根据name给每个人排好序
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// 现在只是在一个voter的循环中
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i; //不用名字，直接把candidate的编码赋值进来
            //ranks[0] = 2 表明了这个voter对于最高分给了candidates[2]
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
// 在这个voter的循环中，给每个 candidate pair 加分
// 假如ranks[0] = 2，说明preference[ranks[0]][ranks[1]]= preference[2][1]
// preferences[ranks[0]][ranks[1]] 就是preference[2][3]
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// 投票都投完了，决定每个pair中谁更被preferred
// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) //这里是ij即可，不用看顺序，因为所有的preference对都要遍历到
            {
                pairs[pair_count].winner = i; //pair_count之前已经初始化到了0
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// 对pair[i]调整顺序
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
        //在每个pair中，如果第一个preference的pair大于其他pair，就锁定这个pair是max的
    {
        int max = i; //第一轮max=0，下面寻找最大的数；第二轮pair[0]里已经放了最大的数，max重置为1，找1位置及其之后的数字中最大的数
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[max].winner][pairs[max].loser])
            {
                max = j;
            }
        } //循环完已经找到最大的那一个pair了
        pair temp = pairs[i];
        //定义一个temp， 是pair数据类型，能够暂放pairs[i]中的两个数据.先把pair[i]暂时放入到temp中
        pairs[i] = pairs[max]; //把这个pair[max]放到[i]的位置
        pairs[max] = temp; //原来pair[max]放入pairs[i]
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].loser, pairs[i].winner))  //不是circle这个locked就设置为true
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    }
    return;
}


bool cycle(int loser, int winner)
//判断是否是circle
//检验每一pair里的winner和loser
//(例如: 1. pair[0]中目前B打败了C，一开始都是false，直接记录locked[B][C]=true)
//2. 检验pair[1]中的C->A是否存在循环
//3. 检验pair[2]中的A->B是否存在循环
{
    // if path exist
    if (locked[loser][winner] == true)
        //如果pair里存在loser->winner，则circle存在 （2.1 检查A-->C有lock吗？没有则下一步）
        //3.1 B-->A false
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++) //检验winner和其他candidate的关系
    {
        // check if winner is locked
        if (locked[i][winner])
            //如果存在i打败了winner的情况 （2.3.1 检验A-->C，B-->C，C-->C）
            //检查所有和winner A的关系，发现C-A存在，return cycle(B, C), locked[loser][winner] == true, 则该关系无法建立
        {
            return cycle(loser, i); //检验其他candidate -> winner 存在，检验 loser的情况 是否存在 -> i的情况
            // (2.3.2 其中B-->C存在，则cycle(A,B), 目前除了bc都是false。结束，locked[A][C]=true)
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool isLoser = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i]) //对于这个i，只要存在locked[j][i]，isLoser就被标记为true，没有被标记上的就是candidates
            {
                isLoser = true;
                break;
            }
        }
        if (isLoser)
        {
            continue;
            //只要被标记上了，就continue到下一个candidate
        }
        str
        if (!isLoser) //如果没有被标记上，就是candidate
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}

// https://gist.github.com/ndiecodes/c6b18883870681fa84c17126ead8ed05