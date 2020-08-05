"use strict";
function handleChange() {
    console.log('oninput事件触发。div：a我input了');
}
function handleKeyDown() {
    console.log('onkeydown触发。div：a我keydown了');
}
const elem = document.getElementById('text');
// abstract class Game {
//     abstract initialize(): void;
//     abstract startPlay(): void;
//     abstract endPlay(): void;
//     // 模版
//     // 此方法不能被子类重写
//     play(): void {
//         this.initialize();
//         this.startPlay();
//         this.endPlay();
//     }
// }
// class Cricket extends Game {
//     initialize(): void {
//         throw new Error("Method not implemented.");
//     }
//     startPlay(): void {
//         throw new Error("Method not implemented.");
//     }
//     endPlay(): void {
//         throw new Error("Method not implemented.");
//     }
//     play() {
//         console.log('重写')
//     }
// }
// var a = 1;
// var obj = {
//     a: 2,
//     foo: foo
// }
// function foo() {
//     console.log(a);
//     console.log(this.a);
// }
// foo(); // 1 // 1
// obj.foo(); // 1 // 2
// 全局执行环境
// GlobalExectionContext = {
//     // 1. 绑定 this
//     this: window,
//     LexicalEnvironment: { // 词法环境
//         EnvironmentRecord: { // 环境记录 Environment record 
//             Type: 'Object environment record', // 类型：对象环境记录 Object environment records
//             foo: pointer to function foo,
//         },
//         outer: <null> // 外部词法环境 outer
//     },
//     VariableEnvironment: { // 变量环境 Varible Environment
//         EnvironmentRecord: { // 环境记录 Environment record 
//             Type: 'Object environment record', // 类型：对象环境记录 Object environment records
//             a: undefined,
//             obj: undefined,
//             foo: pointer to function foo,
//         },
//         outer: <null>
//     }
// }
var a = 10;
var a = 20;
//# sourceMappingURL=index.js.map