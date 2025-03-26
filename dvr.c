#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define INF INT_MAX
struct Link{
    int source,destination,weight;
};
void belman(int nodes,int links,int source,struct Link link[])
{
    int distance[nodes];
    for(int i=0;i<nodes;i++)
    {
        distance[i]=INF;
    }
    distance[source]=0;
    for(int i=0;i<nodes-1;i++)
    {
        for(int j=0;j<links;j++)
        {
            int u=link[j].source;
            int v=link[j].destination;
            int w=link[j].weight;
            if(distance[u]!=INF && distance[u]+w<distance[v])
            {
                distance[v]=distance[u]+w;
            }
        }
    }
    for(int i=0;i<links;i++)
    {
        int u=link[i].source;
        int v=link[i].destination;
        int w=link[i].weight;
        if(distance[u]!=INF && distance[u]+w<distance[v])
        {
            printf("negative cycle\n");
            return;
        }
    }
    printf("Node\tDistance from Source\n");
    for(int i=0;i<nodes;i++)
    {
        printf("%d\t%d\n",i,(distance[i]==INF)?-1:distance[i]);
    }
}
int main()
{
    int nodes,links,source;
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);
    printf("Enter number of links: ");
    scanf("%d", &links);
    struct Link link[links];
    for (int i = 0; i < links; i++) 
    {
        printf("Enter source, destination, weight for link %d: ", i + 1);
        scanf("%d %d %d", &link[i].source, &link[i].destination, &link[i].weight);
    }
    printf("Enter source node: ");
    scanf("%d", &source);
    belman(nodes, links, source, link);

    return 0;

}
