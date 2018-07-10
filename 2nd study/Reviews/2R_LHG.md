#### 1. class 내부에서 1개 이상의 static 또는 const 멤버 선언이 가능한지 여부를 조사하고 이유를 서술하시오.

```
한 Class 내부에 static 멤버 변수,함수와 const 멤버 변수,함수는 여러개 선언 가능하다.
클래스마다 static 멤버는 1개다라고 적혀있는 뜻은 클래스 인스턴스를 여러개 생성해도 static 멤버는 공통되게 사용된다는 뜻(한 인스턴스의 static 변수 값을 바꾸면 다른 인스턴스의 static 변수 값도 같이 바뀜)으로 class 정의 시 한개를 쓰든 여러개를 쓰든 영향이 가지 않는다.
const는 한번 초기화 하면 바뀌지 않는 상수이므로 한개든 여러개든 상관없음.
```

#### 2. 초기화 섹션을 사용하는 이유에 대해 조사하고 초기화 섹션을 사용할 때와 사용하지 않았을 때의 차이점에 대하여 서술하시오.

```
예)const 멤버변수를 사용할때 생성자 초기화 섹션에서 사용한다. 초기화 섹션을 이용하지 않고 {}문 안에서 초기화를 시키면 compile error가 발생하는데, const 멤버변수 특성상 한번 초기화가 되면 값이 바뀌지 않는다. 그래서 생성자를 호출할땐 이미 변수가 쓰레기 값을 가지고 초기화가 되기 때문에 방지하기 위해 compile error가 난다. 초기화 섹션에서 const 멤버변수를 초기화 시켜주면 아예 초기화 시켜준 값으로 초기화가 된다.
일반 변수로는 육안의 차이는 느끼지 못함.
결론: const 멤버변수를 통한 결론 도출 -> 초기화 섹션을 이용하면 아예 초기화 시키려는 값으로 초기화가 진행되고, 초기화 섹션을 이용하지 않는다면 먼저 임의의 쓰레기 값으로 초기화가 되고 {}문 안에서 다시 초기화를 진행해준다.
```

#### 3. default 생성자의 동작에 대해 설명하시오.

```
default 생성자는 클래스에서 생성자가 없을 경우 컴파일러에서 제공하는 기본 생성자다.
매개 변수가 없다.
```

#### 4. default 복사 생성자의 동작에 대해 설명하시오.

```c++
default 복사 생성자는 클래스에서 복사 생성자가 없을 경우 컴파일러에서 제공하는 기본 생성자다.
class A{
private:
	int a;
public:
/*
A(const A &T){
	a = T.a;
}--> 이런 복사 생성자 코드가 없으면 컴파일러가 자동으로 생성해줌
*/
}
int main(){
    A AA;
    A B(AA);
}	// AA 인스턴스에 있는 인수 a 값이 B 인스턴스에 있는 a값으로 복사 됨.
```

#### 5. default 소멸자가 존재하는지 조사하고 생성자와 소멸자의 호출관계에 대하여 설명하시오.

```
default 소멸자도 존재. 컴파일러가 소멸자가 없다면 자동으로 생성 해준다. 기본 소멸자는 아무 일도 하지 않고 단순히 리턴하도록 만들어진다. 소멸자 선언의 반대 순서로 호출됨.
```

#### 6. 깊은복사와 얕은복사에 대해 조사하고 각각의 동작을 예시를 들어 설명하시오.

```c++
얕은 복사 -> 포인터형을 복사 할 때, 생성자에 포인터형을 넘겨주어 복사하면 둘다 포인터가 같은 주소를 가르키는 문제가 발생.
깊은 복사 -> 클래스 자체를 주소 연산자로 받아 와서 포인터 형을 복사할때 힙에 독립적인 공간에 생성해서 복사 함.
class myClass
{
private:
    int a;
    char *name;
public:
    myClass(){}
    myClass(int _a, const char *_name){	// ->> 얕은 복사
        a = _a;
        name = new char[strlen(_name)+1];
        strcpy(name,_name);
    }
    myClass(const myClass &T){	// ->> 깊은 복사
        a = T.a;
        name = new char[strlen(T.name)+1];
        strcpy(name,T.name);
    }
}
int main(){
    myClass A(4,"ant man");
    myClass B(A);
}
```

#### 7. 복사 생성자가 필요한 이유에 대해 설명하시오.

```c++
6번 설명을 토대로 인스턴스의 내용을 복사해서 넘기고 싶을때.
myClass A(4,"ant man");
myClass B(A);
는
myClass A(4,"ant man");
myClass B = A; // 여기서 생성자가 발생하지 않음. 소멸자만 2번 생성되서 프로그램 비정상 종료.
과 같은 맥락이다. 하지만 인스턴스끼리는 기본 = 연산자가 안되기 때문에 일일히 연산자 오버로딩을 해줘야한다. 복사를 편하게 하기 위해 복사 생성자가 필요하다.
```

#### 8. this 포인터에 대해 설명하고 this 포인터를 사용하는 예시를 3가지 이상 작성하시오.

```c++
this 포인터는 class, struct, union 형식의 비정적 멤버 함수에서만 액세스 가능한 포인터이며, 멤버 함수가 호출되는 개체를 가리킨다.
1. 개체의 주소를 멤버 함수 안에서 this 포인터로 사용 가능.
void Date::setMonth( int mn )  //출처 https://msdn.microsoft.com/ko-kr/library/y0dddwwd.aspx
{  
   month = mn;            // 3가지 형식 다 동일함.
   this->month = mn;      //
   (*this).month = mn;  
}  
2. 멤버 함수에서 현재 개체를 반환하기 위해 *this 식을 사용
return *this;
3. this 포인터를 사용해서 자신에 대한 참조를 막음.
    if(&myObj != this){
        /* code */
    }
```
