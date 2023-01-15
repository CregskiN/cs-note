# Decorators 装饰器

## 在类中的应用

+   类装饰器作用于 class
+   方法装饰器作用于函数、成员方法
+   访问器装饰器作用于 getter setter
+   属性装饰器作用于实例成员、静态成员
+   参数装饰器作用于构造函数、方法、访问器

装饰器执行顺序：从下到上，从右到左



## 1. 类装饰器

作为类装饰器的函数，形参为类的构造函数。

对类做且仅做一次修饰。

场景一：修改构造函数

```typescript
@sealed
class BugReport {
  type = "report";
  title: string;

  constructor(t: string) {
    this.title = t;
  }
}

function sealed(constructor: Function) {
  Object.seal(constructor);
  Object.seal(constructor.prototype);
}
```

场景二：工厂模式扩充原构造函数

```typescript
function reportableClassDecorator<T extends { new (...args: any[]): {} }>(constructor: T) {
  return class extends constructor {
    reportingURL = "http://www...";
  };
}

@reportableClassDecorator
class BugReport {
  type = "report";
  title: string;

  constructor(t: string) {
    this.title = t;
  }
}

const bug = new BugReport("Needs dark mode");
console.log(bug.title); // Prints "Needs dark mode"
console.log(bug.type); // Prints "report"

bug.reportingURL;
// Property 'reportingURL' does not exist on type 'BugReport'.
console.log((bug as any).reportingURL); // http://www...
```

>   这个例子中有三点需要注意：
>
>   1.   T extends { new (...args: any[]): {} }
>
>        (...args: any[]) => {} 函数类型
>
>        new (...args: any[]): {} 构造函数类型（new 的作用）
>
>        T extends { new (...args: any[]): {} }：T 继承自 构造函数
>
>   2.   类构造函数返回值是函数，作为原构造函数的扩充。且**执行顺序：原构造函数 -> 扩充构造函数**
>
>   3.   TypeScript 不能推断出工厂函数装饰器返回的扩充构造函数中，对类的修改。一种解决办法是：
>
>        ```typescript
>        function reportableClassDecorator() {
>          return function <T extends { new(...args: any[]): {} }>(constructor: T) {
>            console.log(constructor);
>            return class extends constructor {
>              reportingURL = "http://www...";
>            };
>          }
>        }
>             
>        const BugReport = reportableClassDecorator()(
>          class BugReport {
>            type = "report";
>            title: string;
>             
>            constructor(t: string) {
>              this.title = t;
>            }
>          }
>        )
>             
>        const bug = new BugReport("Needs dark mode");
>             
>        bug.reportingURL; // http://www...
>        ```



## 2. 方法装饰器

方法装饰器接受三个参数：

1.   若修饰的是普通方法，则为类的 prototype。若是静态方法，则为类的构造函数
2.   成员的名字
3.   成员的属性修饰符

场景：

```typescript
class Greeter {
  greeting: string;
  constructor(message: string) {
    this.greeting = message;
  }
 
  @enumerable(false)
  greet() {
    return "Hello, " + this.greeting;
  }
}

function enumerable(value: boolean) {
  return function (target: any, propertyKey: string, descriptor: PropertyDescriptor) {
    descriptor.enumerable = value;
  };
}
```

>   1.   方法装饰器在方法定义前执行，且仅执行一次
>   2.   执行顺序：方法装饰器 -> 函数

## 3. 访问器装饰器

访问器装饰器接收参数：同方法装饰器

```typescript
class Point {
  private _x: number;
  private _y: number;
  constructor(x: number, y: number) {
    this._x = x;
    this._y = y;
  }

  @configurable(false)
  get x() {
    return this._x;
  }

  @configurable(false)
  get y() {
    return this._y;
  }
}

function configurable(config: boolean) {
  return function (target: any, peopertyKey: string, descriptor: PropertyDescriptor) {
    descriptor.writable = false;
    descriptor.configurable = false;
  }

}
```

>   1.   访问器装饰器在访问器定义前执行，且仅执行一次
>   2.   执行顺序：访问器装饰器 -> 同步代码



## 4. 属性装饰器

属性装饰器函数接收参数：

1.   静态成员，则为构造函数；实例成员，则为所在类的 prototype
2.   成员名字

场景 1：用属性装饰器，替换成员的 descriptor

```typescript
class People {
  @configurable(true)
  name: string = 'cregskin';
  constructor() {

  }
}

function configurable(value: boolean) {
  return function (target: any, propertyKey: string): any {
    const descriptor: PropertyDescriptor = {
      writable: false
    }
    return descriptor;
  };
}
```

场景 2：



## 5. 参数装饰器

参数装饰器可用于：类构造函数、方法

参数构造器函数接收三个参数：

1.   若修饰静态成员的形参，则为类构造函数；若为实例成员的形参，则为该类的 prototype
2.   成员名字
3.   该形参所在函数的形参列表中的下标，从 0 开始



## 6. 不同装饰器执行顺序

1.   参数装饰器：从右往左
2.   方法装饰器、属性装饰器按书写顺序
3.   类装饰器



## 7. 装饰器使用场景

### 7.1 错误捕获

```typescript
let peopleName: any = undefined;
let peopleAge: any = undefined;

class People {

  @catchError('peopleName 访问出错')
  getName() {
    return peopleName;
  }

  @catchError('peopleAge 访问出错')
  getAge() {
    return peopleAge;
  }
}

function catchError(msg: string) {
  return function (target: Object, peopertyKey: string, descriptor: PropertyDescriptor) {
    const fn = descriptor.value;
    descriptor.value = function () {
      try {
        fn();
      } catch (e) {
        console.log(msg);
      }
    }
  }
}
```

