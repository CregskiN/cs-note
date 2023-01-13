# 类型操作

## 1. keyof 操作符

当操作对象为普通对象，会生成由对象 key 组成的联合类型

```typescript
type Point = { x: number; y: number };
type P = keyof Point; // 等价于 type P = "x" | "y";
```

当操作对象为普通对象，且使用 string 或 number 作为索引类型，则：

```typescript
type Arrayish = { [n: number]: unknown };
type A = keyof Arrayish; // 等价于 type A = number
 
type Mapish = { [k: string]: boolean };
type M = keyof Mapish; // 等价于 type M = string | number
```

注意，以上 M 的类型等价于 string | number，是因为 JavaScript 对象的 key 强制使用字符串，即 `obj[0]` 等价于 `obj["0"]`



## 2. typeof 操作符

`typeof` 在 JavaScript 很常见，可在表达式上下文中使用

```js
// Prints "string"
console.log(typeof "Hello world");
```

TypeScript 加入了 `typeof` 操作符，你可以在类型上下文中得到变量或属性的类型：

```typescript
let s = "hello";
let n: typeof s; // 等价于 let n: string
```

对于基础类型用处不大，但和其他类型操作符结合起来，能精准表达很多模式。比如，`ReturnType<T>` 可以提取函数类型的返回值类型：

```typescript
type Predicate = (x: unknown) => boolean;
type K = ReturnType<Predicate>; // 等价于 type K = boolean
```

但如果对函数声明使用 `ReturnType` ，会有如下报错：

```typescript
function f() {
  return { x: 10, y: 3 };
}
type P = ReturnType<f>;
// 'f' refers to a value, but is being used as a type here. Did you mean 'typeof f'?
```

因值与类型指的不是同一个东西，`ReturnType` 接受的是类型，为得到函数值的类型，可以用 `typeof`：

```typescript
function f() {
  return { x: 10, y: 3 };
}
type P = ReturnType<typeof f>;
// 等价于
type P = {
    x: number;
    y: number;
}
```

### 局限性

TypeScript 明确限制了能使用 `typeof` 的表达式。确切地说，是只能对标识符（例如变量名）、或标识符下的属性使用。

所以要注意，有些场景，你以为能用 `typeof` 实际却不能：

```typescript
// Meant to use = ReturnType<typeof msgbox>
let shouldContinue: typeof msgbox("Are you sure you want to continue?");
// ',' expected.
```



## 3. Indexed Access Types 索引访问类型

用 js 中访问对象属性的方式，构建新类型。

```typescript
type Person = { 
    age: number; 
    name: string; 
    alive: boolean 
};
type Age = Person["age"]; // 等价于 type Age = number
     
type I1 = Person["age" | "name"]; // 等价于 type I1 = string | number

type I2 = Person[keyof Person]; // type I2 = string | number | boolean
 
type AliveOrName = "alive" | "name";

type I3 = Person[AliveOrName]; // type I3 = string | boolean
```

索引本身就有一种类型，匹配写法还可以更随意一些：

```typescript
const MyArray = [
  { name: "Alice", age: 15 },
  { name: "Bob", age: 23 },
  { name: "Eve", age: 38 },
];
 
type Person = typeof MyArray[number];
// 等价于
type Person = {
    name: string;
    age: number;
}
type Age = typeof MyArray[number]["age"]; // type Age = number
// 等价于
type Age2 = Person["age"]; // type Age2 = number
```

但注意，[Type] 内的必须是类型，而不能是值：

```typescript
const key = "age";
type Age = Person[key];
// Type 'key' cannot be used as an index type.
// 'key' refers to a value, but is being used as a type here. Did you mean 'typeof key'?

type key = "age";
type Age = Person[key];
```



## 4. Conditional Types 条件类型

使用条件运算符/三目运算符生成新类型的写法，叫条件类型

```typescript
SomeType extends OtherType ? TrueType : FalseType;
```

在泛型中很好用：

```typescript
interface IdLabel {
  id: number /* some fields */;
}
interface NameLabel {
  name: string /* other fields */;
}
 
function createLabel(id: number): IdLabel;
function createLabel(name: string): NameLabel;
function createLabel(nameOrId: string | number): IdLabel | NameLabel;
function createLabel(nameOrId: string | number): IdLabel | NameLabel {
  throw "unimplemented";
}
```

这四个重载函数，可用条件运算符简写：

```typescript
type NameOrId<T extends number | string> = T extends number
  ? IdLabel
  : NameLabel;
```

>   类型 NameOrId 接受一个泛型 T，T 为 number 或 string。
>
>   T 为 number 吗
>
>   ? type NameOrId = IdLabel
>
>   : type NameOrId = nameLabel

```typescript
function createLabel<T extends number | string>(idOrName: T): NameOrId<T> {
  throw "unimplemented";
}
 
let a = createLabel("typescript"); // let a: NameLabel
 
let b = createLabel(2.8); // let b: IdLabel
 
let c = createLabel(Math.random() ? "hello" : 42); // let c: NameLabel | IdLabel
```

### 条件类型约束

```typescript
type MessageOf<T> = T["message"];
Type '"message"' cannot be used to index type 'T'.
```

直接在泛型中提取 message 属性的类型，会报错。解决方法是给泛型加一个约束：

```typescript
type MessageOf<T extends { message: unknown }> = T["message"];
 
interface Email {
  message: string;
}
 
type EmailMessageContents = MessageOf<Email>; // type EmailMessageContents = string
```

如果希望 MessageOf 只在泛型有 message 属性时才提取类型，其他情况默认为 never 类型。方法是移除泛型约束，加入条件类型：

```typescript
type MessageOf<T> = T extends { message: unknown } ? T["message"] : never;
 
interface Email {
  message: string;
}
 
interface Dog {
  bark(): void;
}
 
type EmailMessageContents = MessageOf<Email>; // type EmailMessageContents = string
 
type DogMessageContents = MessageOf<Dog>; // type DogMessageContents = never
```

再举一个例子：提取数组类型的元素类型，当不为数组类型，则不会处理：

```typescript
type Flatten<T> = T extends any[] ? T[number] : T;
 
// Extracts out the element type.
type Str = Flatten<string[]>; // type Str = string

// Leaves the type alone.
type Num = Flatten<number>; // type Num = number
```

T[number] 可以访问到，以 number 作为索引类型，能访问到的元素的类型



### 在条件类型中推断

TypeScript 提供 infer 操作符，可以将条件运算符 true 分支的类型，引入到条件类型约束中。

举个例子：GetReturnType\<Type> 提取函数类型 Type 的返回值，生成新类型：

```typescript
type GetReturnType<T> = T extends (...args: never[]) => infer Return
? Return
: never;

type Num = GetReturnType<() => number>; // type Str = string

type Str = GetReturnType<(x: string) => string>; // type Str = string
 
type Bools = GetReturnType<(a: boolean, b: boolean) => boolean[]>; 
// type Bools = boolean[]
```



### 分配条件类型

对联合类型使用条件运算符，会将类型推断应用到联合类型的每个成员：

```typescript
type ToArray<Type> = Type extends any ? Type[] : never;
 
type StrArrOrNumArr = ToArray<string | number>;        
// type StrArrOrNumArr = string[] | number[]
```

等价于：

```typescript
string | number
-> ToArray<string> | ToArray<number>
-> string[] | number[]
```

以上写法，输入的是联合类型，输出也是联合类型。

但我们想要输出的是联合类型数组，这种分布到联合类型每个成员的特性，很烦人。解决办法是：

```typescript
type ToArrayNonDist<Type> = [Type] extends [any] ? Type[] : never;
 
// 'StrOrNumArr' 不再是一个联合类型
type StrOrNumArr = ToArrayNonDist<string | number>;
// type StrOrNumArr = (string | number)[]
```



## 5. Mapped Types 映射类型

映射类型的应用场景是，用已有类型生成新类型。

映射类型是一种泛型，该泛型遍历 PropertyKeys（用 keyof 生成） 的 key 生成一个新类型：

```typescript
type OptionsFlags<Type> = {
  [Property in keyof Type]: boolean;
};

type FeatureFlags = {
  darkMode: () => void;
  newUserProfile: () => void;
};
 
type FeatureOptions = OptionsFlags<FeatureFlags>;
// 等价于   
type FeatureOptions = {
    darkMode: boolean;
    newUserProfile: boolean;
}
```



### 类型修改器

+、- 可以增、删在映射中使用的修饰符，如 readonly、?

第一个例子：删除 readonly 修饰符

```typescript
// 取消 Type 属性的 readonly 修饰符
type CreateMutable<Type> = {
  -readonly [Property in keyof Type]: Type[Property];
};
 
type LockedAccount = {
  readonly id: string;
  readonly name: string;
};
 
type UnlockedAccount = CreateMutable<LockedAccount>;
// 等价于
type UnlockedAccount = {
    id: string;
    name: string;
}
```

第二个例子：将 ? 可选修饰符删除

```typescript
// Removes 'optional' attributes from a type's properties
type Concrete<Type> = {
  [Property in keyof Type]-?: Type[Property];
};
 
type MaybeUser = {
  id: string;
  name?: string;
  age?: number;
};
 
type User = Concrete<MaybeUser>;
// 等价于
type User = {
    id: string;
    name: string;
    age: number;
}
```



### 通过 as 重映射键

场景一：将 Person 的 key 修改为 getKey，值修改为 () => originReturnType

```typescript
type Getters<Type> = {
    [Property in keyof Type as `get${Capitalize<string & Property>}`]: () => Type[Property]
};
 
interface Person {
    name: string;
    age: number;
    location: string;
}
 
type LazyPerson = Getters<Person>;
         
type LazyPerson = {
    getName: () => string;
    getAge: () => number;
    getLocation: () => string;
}
```

>   模版文本类型\``是一个 TypeScript 4.1 添加的功能，截止到 Typora 1.2.3 内置的语法也不能识别。

场景二：删除 Circle 的属性 kind: "circle"

```typescript
// Remove the 'kind' property
type RemoveKindField<Type> = {
    [Property in keyof Type as Exclude<Property, "kind">]: Type[Property]
};
 
interface Circle {
    kind: "circle";
    radius: number;
}
 
type KindlessCircle = RemoveKindField<Circle>;
// 等价于        
type KindlessCircle = {
    radius: number;
}
```

场景三：对联合类型映射

```typescript
type EventConfig<Events extends { kind: string }> = {
    [E in Events as E["kind"]]: (event: E) => void;
}
 
type SquareEvent = { kind: "square", x: number, y: number };
type CircleEvent = { kind: "circle", radius: number };
 
type Config = EventConfig<SquareEvent | CircleEvent>
// 等价于
type Config = {
    square: (event: SquareEvent) => void;
    circle: (event: CircleEvent) => void;
}
```



>   以下部分挺复杂的，不是库开发者我觉得没必要了解，以后再做整理

### 进一步探索

Mapped types work well with other features in this type manipulation section, for example here is [a mapped type using a conditional type](https://www.typescriptlang.org/docs/handbook/2/conditional-types.html) which returns either a `true` or `false` depending on whether an object has the property `pii` set to the literal `true`:

```
type ExtractPII<Type> = {
  [Property in keyof Type]: Type[Property] extends { pii: true } ? true : false;
};
 
type DBFields = {
  id: { format: "incrementing" };
  name: { type: string; pii: true };
};
 
type ObjectsNeedingGDPRDeletion = ExtractPII<DBFields>;
                 
type ObjectsNeedingGDPRDeletion = {
    id: false;
    name: true;
}
```

