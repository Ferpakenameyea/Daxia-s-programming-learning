# Daxia-s-programming-learning
This is for MC DAXIA and their buddies to learn C PROGRAMMING!

# Daxias C Programming STYLE!
## OOC!  Fuck Procedure Oriented Programming!
```C
#define new(Type) (Type*)malloc(sizeof(Type))
```
## Create full-name variables! STOP USING ABBREVIATIONS!!!!!!!
```C
//POOP AND CRAP!!!
int x, y, z, a, b, c;
//GOOD!!! ZBC!!!
int matrixSize;
```

## STOP PUTTING ALL THINGS IN main() FUNCTION!!! LEARN TO CREATE YOUR OWN FUNCTION!!!!
```C
//POOP AND SHIT!!!
int main(){
  int vectorX, vectorY, vectorZ;
  int vector2X, vector2Y, vector2Z;
  scanf("%d%d%d", &vectorX, &vectorY, &vectorZ);
  scanf("%d%d%d", &vector2X, &vector2Y, &vector2Z);
  printf("%d\n", vectorX * vector2X + vectorY * vector2Y + vectorZ * vector2Z);
}

//GOOD!!!
typedef struct Vector3{
  int x, y, z;
} Vector3;

int DotMultiple(Vector3 a, Vector3 b){
  return a.x * b*x + a.y * b.y + a.z * b.z;
}

int main(){
  //write write write!
  Vector3 vecA, vecB;
  scanf("%d%d%d", &vecA.x, &vecA.y, &vecA.z);
  scanf("%d%d%d", &vecB.x, &vecB.y, &vecB.z);
  printf("%d\n", DotMultiple(vecA, vecB));
}
```
