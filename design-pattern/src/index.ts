
function unWritable(target: any, key: any, descriptor: PropertyDescriptor) {
    descriptor.writable = false;
}

interface IGame {
    readonly play: () => void;
}

class Game implements IGame {
    play: () => void;
    constructor() {
        this.play = () => {
            console.log('未重写')
        }
    }
}




class Cricket extends Game {
    play: () => void;
    constructor() {
        super();
        this.play = () => {
            console.log('重写');
        }
    }
}
const c = new Cricket();
c.play();


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
