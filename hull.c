#include <stdio.h>
#include <stdlib.h>
struct points
{
    int x;
    int y;
};
int tos=-1;
struct points stackofhull[1000];
void push(struct points p)
{
    tos++;
    stackofhull[tos]=p;
}
void pop()
{
    tos--;
}
void display()
{
    int i;
    for(i=0;i<=tos;i++)
    {
        printf("%d %d\n",stackofhull[i].x,stackofhull[i].y);
    }
}
int dist(struct points p1,struct points p2)
{
    int x=p2.x-p1.x;
    int y=p2.y-p1.y;
    int dist=(x*x)+(y*y);
    return dist;
}

int orientation(struct points p1,struct points p2,struct points p3)
{
    int x1=p1.x-p3.x;
    int y1=p1.y-p3.y;
    int x2=p2.x-p3.x;
    int y2=p2.y-p3.y;
    int ort=(x1*y2)-(x2*y1);
    return ort;
}
void merge(struct points a[], int start,int mid,int end,struct points ref)
{
     int p=start;
    int q=mid+1;
     struct points arr[end-start+1];
    int i,k=0;
    for(i=start;i<=end;i++)
    {
        if(p>mid)
        {
            arr[k]=a[q];
            k++;
            q++;
        }
        else if(q>end)
        {
            arr[k++]=a[p++];

        }
        else if(orientation(a[p],a[q],ref)>0)
        {
            arr[k++]=a[p++];


        }
        else if(orientation(a[p],a[q],ref)==0)
        {
            if(dist(ref,a[p])<dist(ref,a[q]))
            {
                arr[k++]=a[p++];
            }
            else
               arr[k++]=a[q++];


        }
        else
        {
        arr[k]=a[q];
        k++;
        q++;
        }
    }
    for(i=0;i<k;i++)
    {
        a[start]=arr[i];
        start++;
    }


}
void mergesort( int a[],int start,int end,struct points ref)
{
    if(start<end)
    {
        int mid=(start+end)/2;
        mergesort(a,start,mid,ref);
        mergesort(a,mid+1,end,ref);
        merge(a,start,mid,end,ref);
    }
}
int min(struct points a[],int n)
{
    int min=a[0].y;
    int i,pos=0;
    for(i=0;i<n;i++)
    {
        if(a[i].y<=min)
        {
            min=a[i].y;
            pos=i;
        }
    }
    for(i=0;i<n;i++)
    {
        if(a[i].y==a[pos].y && a[i].x<a[pos].x)
        {
            pos=i;
        }

    }
   return pos;
}

void Grahamscan(struct points a[],int n)
{
  int pos=min(a,n);
  struct points ref;
  ref=a[pos];
  int start=0;
  int end=n-1;
  mergesort(a,start,end,ref);
  int i;
 // for(i=0;i<n;i++)
  //{
    //  printf("%d %d",a[i].x,a[i].y);
  //}
  printf("\n");
  struct points ar[n];
  int m=0;
  i=0;
  while(i<n)
  {
      while(i<n-1 &&(orientation(a[i],a[i+1],ref)==0))
      {
       i++;
      }
      ar[m]=a[i];
      m++;
      i++;
  }
  //for(i=0;i<m;i++)
  //{
    //  printf("%d %d",ar[i].x,ar[i].y);

  //}
  push(ref);
  push(ar[0]);
  push(ar[1]);
  for(i=2;i<m;i++)
  {
      while((orientation(ar[i],stackofhull[tos],stackofhull[tos-1])>0))
            {
                pop();
            }
            push(ar[i]);
  }
   display();
}









int main()
{
    int n;
    int i;
    printf("Enter the number of points\n");
    scanf("%d",&n);
    struct points a[n];
    printf("enter the coordinates\n");
    for(i=0;i<n;i++)
    {
        scanf("%d%d",&a[i].x,&a[i].y);
    }
    Grahamscan(a,n);
    return 0;
}
