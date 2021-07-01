#include <iostream>
#include <string>

//MAXIMUM ELEMENTS ALLOWED
static const int maxSize = 43;
static const int unionSize = 2*maxSize;

 using namespace std; 
 
 // STRUCTURE FOR MY SET
 struct mySet {
     int noElements;
     string myString[maxSize];     
 };
 
 
//STRUCTURE FOR UNION AND OTHER APPLICATIONS
struct myUnion {
    int noElements;
    string myString[unionSize];
};
 
 
 //FUNCTION PROTOTYPES
 mySet *createSet();
 myUnion *createUnion();
 long long int getHash(string &s, char x = 's');
 bool isEmptySet(mySet *checkSet, char x = 's', myUnion *checkUnion =  nullptr );
 int sizeSet(mySet *checkSet, char x = 's', myUnion *checkUnion = nullptr);
 void displaySet(mySet *checkSet, char x = 's', myUnion *checkUnion = nullptr);
 mySet *buildSet(string s[], int n);
 bool isElement(mySet *checkSet, string s, char x = 's' , myUnion *checkUnion= nullptr);
 void addElement(mySet *checkSet , string s, char x= 's', myUnion *checkUnion = nullptr);
 void removeElement(mySet *checkSet, string s, char x = 's', myUnion *checkUnion = nullptr);
 myUnion *unionSet(mySet *set1, mySet *set2);
 mySet *intersectSets(mySet *set1, mySet *set2);
 mySet *differenceSet(mySet *set1, mySet *set2);
 bool isSubset(mySet *set1, mySet *set2);
 void printTF(bool inVal);
 
 
 
 int main() {
     
     //call necessary functions
   
     return 0;
 }

 
 
// CREATES A NEW EMPTY SET
 mySet *createSet() {
     
    mySet *newSet;
    newSet = new mySet;
    
//    cout << "Enter create " << endl;
    
    newSet->noElements = 0;
    
    int i = 0;
    
    for(i=0 ; i<maxSize ; i++) {
        newSet->myString[i] = "null";
    }

    return newSet;
 }
 
 
//CREATES NEW EMPTY UNION
myUnion *createUnion() {
    myUnion *newUnion;
    newUnion = new myUnion;
    
    newUnion->noElements = 0;
    
    int i= 0;
    
    for(i=0 ; i<unionSize ; i++) {
        newUnion->myString[i] = "null";
    }
    
    return newUnion;
}
 
 
// HASHING FUNCTION
 long long int getHash(string &s, char x) {
     
//     cout << "Get hash string " << s << endl;
     const int p = 31;      //multiplying factor
     const int m = 1e9 + 9;
     
     long long int hashVal = 0;
     long long int currPow = 1;
     
     for (char c : s) {
         
         hashVal = (hashVal + (c - 'a' + 1) * currPow) % m;
         currPow = (currPow * p) % m;
     }
     
     if( x == 's'){
         hashVal = (hashVal%maxSize);
     }
     else if( x == 'u') {
         hashVal = (hashVal%unionSize);
     }
     else {
         cout << "Neither set nor union \n" ;
     }
        
    return hashVal;
 }
 
 
// CHECK WHETHER SET IS EMPTY OR NOT
bool isEmptySet(mySet *checkSet, char x, myUnion *checkUnion ) {
    bool isEmpty = false;
    
    if(x == 's') {
        if(checkSet->noElements == 0) {
            isEmpty = true;
        }
    }
    else if( x == 'u') {
        if(checkUnion->noElements == 0) {
            isEmpty = true;
        }
    }
    else {
        cout << "Neither set nor union. Try again. \n";
    }
    
    return isEmpty;
}


//RETURN SIZE OR NO. OF ELEMENTS IN SET
int sizeSet(mySet *checkSet, char x, myUnion *checkUnion) {
    
    int setSize;
    
    if(x == 's') {
        setSize = checkSet->noElements;
    }
    else if( x == 'u' ) {
         setSize = checkUnion->noElements;
    }
    
    return setSize;
}

//DISPLAY ELEMENTS IN ARBITRARY ORDER
void displaySet(mySet *checkSet, char x, myUnion *checkUnion) {
    
    int i =0;
    
    if(x == 's') {
        
        for(i= 0 ; i <maxSize ; i++) {
            
            if( (checkSet->myString[i]) != "null" ) {
                cout << checkSet->myString[i] << endl;
    //            cout << i << endl;
            }

        }
    }
    else if(x == 'u') {
        for(i= 0 ; i <unionSize ; i++) {
            
            if( (checkUnion->myString[i]) != "null" ) {
                cout << checkUnion->myString[i] << endl;
            }

        }
    }
}


//CHECK WHETHER A STRING IS AN ELEMENT OF THE SET OR NOT
bool isElement(mySet *checkSet, string s, char x , myUnion *checkUnion) {
    
    int hashVal = getHash(s, x);
    bool isPresent = false;
    
    if( x== 's') {
        if(checkSet->myString[hashVal] == s) {
            isPresent = true;
        } 
        else {
            int i = hashVal + 1, flagVal = 0;
            int j= (i%maxSize);
            
            while ( j!= hashVal && flagVal == 0) {
                
                if( checkSet->myString[j] == s) {
                    isPresent = true;
                    flagVal = 1;
                }
                
                i++;
                j= (i%maxSize);
                
            }
        }
    }
    else if( x == 'u') {
        
        if(checkUnion->myString[hashVal] == s) {
            isPresent = true;
        } 
        else {
            int i = hashVal + 1, flagVal = 0;
            int j= (i%unionSize);
            
            while ( j!= hashVal && flagVal == 0) {
                
                if( checkUnion->myString[j] == s) {
                    isPresent = true;
                    flagVal = 1;
                }
                
                i++;
                j= (i%unionSize);
                
            }
        }
    }
    
    return isPresent;
}


//INSERT VALUE INTO SET
void addElement(mySet *checkSet , string s, char x, myUnion *checkUnion) {
        
    if ( x == 's' ) {
        
        int hashVal = getHash(s);
    
        cout << "Hash calculated " << hashVal << endl;
        
        int flagVal = 0, i = 0, j = 0;
        
        if(checkSet->noElements == maxSize) {
            cout << "Set full. Cannot insert." << endl;
        }
        else {
            
            if(checkSet->myString[hashVal] == "null") {             //default value of every element is null
                checkSet->myString[hashVal] = s;
                checkSet->noElements ++;
    //            cout << "Insertion successful" << endl;
            }
            else if(isElement(checkSet, s) == true) {
                cout << "";
            }
            else {
                cout << "collision"<< endl;
                cout << s << endl;
                i = hashVal + 1;
                j= (i%maxSize);
                
                while(j != hashVal && flagVal == 0) {
                    
                    if(checkSet->myString[j] == "null") {
                        checkSet->noElements ++;
                        checkSet->myString[j] = s;
                        flagVal = 1;
    //                    cout << "Insertion successful" << endl;
                    }
                    
                    i++;
                    j= i%maxSize;
                }
            }
        }
    
    }
    else if (x == 'u') {
        int hashVal = getHash(s, x);
    
    //    cout << "Hash calculated " << hashVal << endl;
        
        int flagVal = 0, i = 0, j = 0;
        
        if(checkUnion->noElements == unionSize) {
            cout << "Union full. Cannot insert." << endl;
        }
        else {
    //        cout << "Entered else condition \n";
            
            if(checkUnion->myString[hashVal] == "null") {             //default value of every element is null
                checkUnion->myString[hashVal] = s;
                checkUnion->noElements ++;
    //            cout << "Insertion successful" << endl;
            }
            else if(isElement(nullptr, s, x , checkUnion) == true) {
                cout << "";
            }
            else {
                i = hashVal + 1;
                j= (i%unionSize);
                
                while(j != hashVal && flagVal == 0) {
                    
                    if(checkUnion->myString[j] == "null") {
                        checkUnion->noElements ++;
                        checkUnion->myString[j] = s;
                        flagVal = 1;
    //                    cout << "Insertion successful" << endl;
                    }
                    
                    i++;
                    j= i%unionSize;
                }
            }
        }
    }
    else {
        cout << "Neither set nor Union. Try again \n";
    }
}


//REMOVE ELEMENT FROM SET
void removeElement(mySet *checkSet, string t, char x, myUnion *checkUnion) {
    
    if( x == 's') {
        
        if(isElement(checkSet, t) == false) {
            cout << "Element not in set \n";
        }
        else {
            
            int hashVal = getHash(t);
            
            cout << "enter s \n";
            
            if(checkSet->myString[hashVal] == t) {
                
                checkSet->myString[hashVal] = "null";
                checkSet->noElements--;
                cout << "Deletion successful \n";
                
            }
            else {
                
                int i = hashVal + 1;
                int flagVal = 0;
                int j = i%maxSize;
                
                while( j != hashVal && flagVal == 0) {
                    
                    if(checkSet->myString[j] == t) {
                        
                        checkSet->myString[j] = "null";
                        checkSet->noElements--;
                        
                        cout << "Deletion successful \n";
                        flagVal = 1;
                    }
                    
                    i++;
                    j = i%maxSize;
                }
            }
            
        }
    }
    else if( x == 'u') {
        
        if(isElement(nullptr, t, x, checkUnion) == false) {
            cout << "Element not in set \n"<< endl;;
        }
        else {
            
            int hashVal = getHash(t);
            
            if(checkUnion->myString[hashVal] == t) {
                checkUnion->myString[hashVal] = "null";
                checkUnion->noElements--;
                cout << "Deletion successful \n";
            }
            else {
                int i = hashVal + 1;
                int flagVal = 0;
                int j = i%unionSize;
                
                while( j != hashVal && flagVal == 0) {
                    
                    if(checkUnion->myString[j] == t) {
                        checkUnion->myString[j] = "null";
                        checkUnion->noElements--;
                        cout << "Deletion successful \n";
                        flagVal = 1;
                    }
                    
                    i++;
                    j = i%unionSize;
                }
            }
            
        }        
    }
    else {
        cout << "Neither set nor Union. Try again \n";
    }
    
}


//CREATE UNION OF SETS
myUnion *unionSet(mySet *set1, mySet *set2) {
    
    myUnion *newUnion;
    newUnion = createUnion();
    
    int i =0;
        
    for( i = 0; i< maxSize; i++) {
        addElement(nullptr, set1->myString[i] , 'u', newUnion);        
    }
    
    for( i =0 ; i<maxSize ; i++) {
        addElement(nullptr, set2->myString[i], 'u', newUnion);
    }
    
    return newUnion;
    
}

//INTERSECTION OF 2 SETS
mySet *intersectSets(mySet *set1, mySet *set2) {
    
//    cout << "Enter intersect \n";
    
    mySet *newSet;
    newSet = new mySet;
    
    newSet = createSet();
    
    int i =0;
    int elNo;
                                                    //the maximum size of an intersection will be the size of the smaller set
    if(set1->noElements < set2->noElements) {
        
        elNo = set1->noElements;
        
        while(i<maxSize && elNo>0) {
            if(set1->myString[i] != "null")  {
                
                if(isElement(set2, set1->myString[i]) == true) {
                     addElement(newSet, set1->myString[i]);
                }
                
                elNo --;
               
            }
            
            i++;
        }
    }
    else {
        
        elNo = set2->noElements;
        
        while(i<maxSize && elNo>0) {
            if(set2->myString[i] != "null") {
                
                if(isElement(set1, set2->myString[i]) == true) {
                    addElement(newSet, set2->myString[i]);
                }
                
                elNo--;
            }
            i++;
        }
        
    }
//    cout << "Intersection formed \n";    
    return newSet;
}


//DIFFERENCE OF SETS
mySet *differenceSet(mySet *set1, mySet *set2) {
    
    mySet *diffSet;
    diffSet = createSet();
    int i =0;
    
    for(i=0 ; i<maxSize ; i++) {
        if((set1->myString[i]) != "null" && isElement(set2, set1->myString[i]) == false) {
            addElement(diffSet,  set1->myString[i]);
        }
    }
    
    return diffSet;
}


//SUBSET OF A SET
bool isSubset(mySet *set1, mySet *set2) {
    
    int count = 0, i = 0;
    bool subSet = false;
    
    for(i =0 ; i< maxSize ; i++) {
        
        if(set1->myString[i] != "null" && isElement(set2, set1->myString[i]) == true) {
            count ++;
        }
        
    }
    
    if(count == set1->noElements) {
        subSet = true;
    }
    
    return subSet;
    
}

    

//PRINTS THE OUTPUT OF A BOOLEAN VALUE
void printTF(bool inVal) {
     
    if(inVal == true ) {
        cout << "True" << endl;
    }
    else {
        cout << "False" << endl;
    }
}


//BUILD A SET WITH N VALUES
mySet *buildSet(string s[], int n) {
    
    mySet *newSet;
    newSet = new mySet;
    
    newSet = createSet();
    
    int i = 0;
    
    for(i = 0; i <n ; i++) {
        
        addElement(newSet, s[i]);
        
    }
    
    return newSet;
}
