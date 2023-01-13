# TypeScript Utility Types

Utility Types 工具类型。



## Awaited\<Type>



## Partial\<Type> & Required\<Type>

Partial\<Type> 将 Type 中所有属性设置为可选

```typescript
interface Todo {
  title: string;
  description: string;
}
type OptionalTodo = Partial<Todo>;
// 等价于
interface OptionalTodo {
    title?: string;
    description?: string;
}
```

Required\<Type> 相反，将 Type 所有属性设置为必选

```typescript
interface Todo {
  title?: string;
  description: string;
}
type MandatoryTodo = Partial<Todo>;
// 等价于
interface MandatoryTodo {
    title: string;
    description: string;
}
```



## Readonly\<Type>

Readonly\<Type> 将 Type 所有属性设置为只读，即对该对象属性的修改会报错

```typescript
interface Todo {
  title: string;
}
 
const todo: Readonly<Todo> = {
  title: "Delete inactive users",
};
 
todo.title = "Hello"; // Cannot assign to 'title' because it is a read-only property.
```

>   其效果类似于对对象使用 Object.freeze()，函数签名如下：

```typescript
function freeze<Type>(obj: Type): Readonly<Type>;
```



## Record\<Keys, Type>

Record\<Keys, Type> 构建一个对象类型，其中对象的键 key 必须为 Keys，值类型必须为 Type

```typescript
interface CatInfo {
  age: number;
  breed: string;
}
 
type CatName = "miffy" | "boris" | "mordred";
 
const cats: Record<CatName, CatInfo> = {
  miffy: { age: 10, breed: "Persian" },
  boris: { age: 5, breed: "Maine Coon" },
  mordred: { age: 16, breed: "British Shorthair" },
};
 
cats.boris;
```

>   注意，此处 cats 对象的 key 必须有且只有 "miffy"、"boris"、"mordred"



## Pick\<Type, Keys> & Omit<Type, Keys>

Pick\<Type, Keys> 从 Type 中挑选制定 Keys，组成一个新类型

```typescript
interface Todo {
  title: string;
  description: string;
  completed: boolean;
}
 
type PickTodo = Pick<Todo, "title" | "completed">;
// 等价于
interface PickTodo {
    title: string;
    completed: boolean;
}
```

Omit\<Type, Keys> 从 Type 中剔除 Keys，组成一个新类型

```typescript
interface Todo {
  title: string;
  description: string;
  completed: boolean;
  createdAt: number;
}
 
type TodoPreview = Omit<Todo, "description">;
// 等价于
interface Todo {
  title: string;
  completed: boolean;
  createdAt: number;
}
```

## Exclude\<UnionType, ExcludedMembers>

Exclude\<UnionType, ExcludedMembers> 从 UnionType 中剔除 ExcludedMembers 成员，构建新类型

```typescript
type T0 = Exclude<"a" | "b" | "c", "a">;
// 等价于
type T0 = "a";

type T1 = Exclude<"a" | "b" | "c", "a" | "b">;
// 等价于
type T1 = "c"

type T2 = Exclude<string | number | (() => void), Function>;
// 等价于
type T2 = string | number
```

>   类似 Omit，区别是 Omit 针对 type 和 interface 定义的类型，Exclude 针对联合类型。更具体的分析，请看：[[TypeScript] Omit 和 Exclude 类型的区别与用法](https://www.fullstackbb.com/typescript/difference-between-omit-and-exclude-in-typescript/#:~:text=%E9%A1%BE%E5%90%8D%E6%80%9D%E4%B9%89%EF%BC%8C%20Exclude%20%E7%9A%84%E7%AC%AC%E4%B8%80%E4%B8%AA%E5%8F%82%E6%95%B0%E6%98%AF%E4%B8%80%E4%B8%AA%E8%81%94%E5%90%88%E7%B1%BB%E5%9E%8B%EF%BC%8C%20%E8%80%8C%20Omit%3CType%2C%20Keys%3E%20%E7%9A%84%E8%A7%A3%E9%87%8A%E6%98%AF%EF%BC%9A%E5%8F%96%20Type,interface%20%E4%B8%8A%E7%9A%84%E3%80%82%20Omit%20%E7%9A%84%E5%86%85%E9%83%A8%E4%BD%BF%E7%94%A8%E4%BA%86%20Exclude%20%E6%9D%A5%E5%8F%96%20Keys%20%E3%80%82)



## Extract<Type, Union>

Extract<Type, Union> 从 Type 中提取可加入到 Union 的 Type 成员，构建一个新类型

```typescript
type T0 = Extract<"a" | "b" | "c", "a" | "f">;
// 等价于
type T0 = "a"

type T1 = Extract<string | number | (() => void), Function>;
// 等价于     
type T1 = () => void
```

## NonNullable\<Type>

NonNullable\<Type> 剔除 Type 中的 undefined、null 类型，构建一个新类型

```typescript
type T0 = NonNullable<string | number | undefined>;
// 等价于
type T0 = string | number

type T1 = NonNullable<string[] | null | undefined>;
// 等价于     
type T1 = string[]
```



## Parameters\<Type>

Parameters\<Type> 在函数 Type 中提取出形参类型，构建一个新类型

```typescript
declare function f1(arg: { a: number; b: string }): void;
 
type T0 = Parameters<() => string>; // 等价于 type T0 = []
type T1 = Parameters<(s: string) => void>; // 等价于 type T1 = [s: string]
type T2 = Parameters<<T>(arg: T) => T>; // 等价于 type T2 = [arg: unknown]
    
type T3 = Parameters<typeof f1>;
// 等价于
type T3 = [arg: {
    a: number;
    b: string;
}]

type T4 = Parameters<any>; // 等价于 type T4 = unknown[]

type T5 = Parameters<never>; // 等价于 type T5 = never

type T6 = Parameters<string>;  // 等价于 type T6 = never
// Type 'string' does not satisfy the constraint '(...args: any) => any'.

type T7 = Parameters<Function>; // 等价于 type T7 = never
// Type 'Function' does not satisfy the constraint '(...args: any) => any'.
//  Type 'Function' provides no match for the signature '(...args: any): any'.
```



## ConstructorParameters\<Type>

ConstructorParameters\<Type> 提取构造函数类型 Type 的形参类型，构建一个新类型

```typescript
type T0 = ConstructorParameters<ErrorConstructor>;
     
type T0 = [message?: string]
type T1 = ConstructorParameters<FunctionConstructor>;
     
type T1 = string[]
type T2 = ConstructorParameters<RegExpConstructor>;
     
type T2 = [pattern: string | RegExp, flags?: string]
type T3 = ConstructorParameters<any>;
     
type T3 = unknown[]
 
type T4 = ConstructorParameters<Function>;
Type 'Function' does not satisfy the constraint 'abstract new (...args: any) => any'.
  Type 'Function' provides no match for the signature 'new (...args: any): any'.
     
type T4 = never
```



## ReturnType\<Type>

ReturnType\<Type> 提取一个函数类型 Type 返回值的类型，构建一个新类型

```typescript
declare function f1(): { a: number; b: string };
 
type T0 = ReturnType<() => string>; // 等价于 type T0 = string

type T1 = ReturnType<(s: string) => void>; // type T1 = void

type T2 = ReturnType<<T>() => T>; // type T2 = unknown

type T3 = ReturnType<<T extends U, U extends number[]>() => T>; // type T3 = number[]

type T4 = ReturnType<typeof f1>; // 等价于 type T4 = { a: number; b: string; }

type T5 = ReturnType<any>; // type T5 = any

type T6 = ReturnType<never>; // type T6 = never

type T7 = ReturnType<string>; // type T7 = any
// Type 'string' does not satisfy the constraint '(...args: any) => any'.

type T8 = ReturnType<Function>; // type T8 = any
// Type 'Function' does not satisfy the constraint '(...args: any) => any'.
// Type 'Function' provides no match for the signature '(...args: any): any'.
```



## InstanceType\<Type>

InstanceType\<Type> 提取构造函数的实例类型，构建一个新类型

```typescript
class C {
  x = 0;
  y = 0;
}
 
type T0 = InstanceType<typeof C>;
     
type T0 = C
type T1 = InstanceType<any>;
     
type T1 = any
type T2 = InstanceType<never>;
     
type T2 = never
type T3 = InstanceType<string>;
Type 'string' does not satisfy the constraint 'abstract new (...args: any) => any'.
     
type T3 = any
type T4 = InstanceType<Function>;
// Type 'Function' does not satisfy the constraint 'abstract new (...args: any) => any'.
// Type 'Function' provides no match for the signature 'new (...args: any): any'.
     
type T4 = any
```



## ThisParameterType\<Type>

ThisParameterType\<Type> 提取函数类型 Type 中名为 this 的形参的类型，构建一个新类型。如果没有 this 形参，则该新类型为 unknown

```typescript
function toHex(this: Number) {
  return this.toString(16);
}
 
function numberToString(n: ThisParameterType<typeof toHex>) {
  return toHex.apply(n);
}
```



## OmitThisParameter\<Type>

>   这个我没看懂说明，也没用到过，放档案原文：

Removes the [`this`](https://www.typescriptlang.org/docs/handbook/functions.html#this-parameters) parameter from `Type`. If `Type` has no explicitly declared `this` parameter, the result is simply `Type`. Otherwise, a new function type with no `this` parameter is created from `Type`. Generics are erased and only the last overload signature is propagated into the new function type.

```typescript
function toHex(this: Number) {
  return this.toString(16);
}
 
const fiveToHex: OmitThisParameter<typeof toHex> = toHex.bind(5);
 
console.log(fiveToHex());
```



## ThisType\<Type>

ThisType\<Type> This utility does not return a transformed type. Instead, it serves as a marker for a contextual [`this`](https://www.typescriptlang.org/docs/handbook/functions.html#this) type. Note that the [`noImplicitThis`](https://www.typescriptlang.org/tsconfig#noImplicitThis) flag must be enabled to use this utility.

```typescript
type ObjectDescriptor<D, M> = {
  data?: D;
  methods?: M & ThisType<D & M>; // Type of 'this' in methods is D & M
};
 
function makeObject<D, M>(desc: ObjectDescriptor<D, M>): D & M {
  let data: object = desc.data || {};
  let methods: object = desc.methods || {};
  return { ...data, ...methods } as D & M;
}
 
let obj = makeObject({
  data: { x: 0, y: 0 },
  methods: {
    moveBy(dx: number, dy: number) {
      this.x += dx; // Strongly typed this
      this.y += dy; // Strongly typed this
    },
  },
});
 
obj.x = 10;
obj.y = 20;
obj.moveBy(5, 5);
```

In the example above, the `methods` object in the argument to `makeObject` has a contextual type that includes `ThisType<D & M>` and therefore the type of [this](https://www.typescriptlang.org/docs/handbook/functions.html#this) in methods within the `methods` object is `{ x: number, y: number } & { moveBy(dx: number, dy: number): number }`. Notice how the type of the `methods` property simultaneously is an inference target and a source for the `this` type in methods.

The `ThisType<T>` marker interface is simply an empty interface declared in `lib.d.ts`. Beyond being recognized in the contextual type of an object literal, the interface acts like any empty interface.



## Uppercase\<StringType>

## Lowercase\<StringType>

## Capitalize\<StringType>

## Uncapitalize\<StringType>