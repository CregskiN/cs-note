"use strict";
function handleChange() {
    console.log('oninput事件触发。div：a我input了');
}
function handleKeyDown() {
    console.log('onkeydown触发。div：a我keydown了');
}
const elem = document.getElementById('text');
class Observer {
    constructor(name) {
        this.name = name;
    }
}
// 用户类
class User extends Observer {
    constructor(name, subject) {
        super(name);
        this.subject = subject;
        this.subject.register(this);
    }
    sendMsg(msg) {
        console.log(`${this.name} 发送了消息，${msg}`);
        this.subject.sendMsg(this, msg);
    }
    receiveMsg(sender, msg) {
        console.log(`${this.name} 收到来自 ${sender.name} 的消息，${msg}`);
    }
}
// 群组
class Group {
    constructor() {
        this.userList = [];
    }
    register(observer) {
        this.userList.push(observer);
    }
    unregister(observer) {
        const index = this.userList.indexOf(observer);
        if (index > -1) {
            this.userList.splice(index, 1);
        }
    }
    sendMsg(sender, msg) {
        console.log(`群组收到${sender.name} 发来的消息，${msg} 通知所有人`);
        this.notify(sender, msg);
    }
    /**
     * 发布通知
     * @param sender
     * @param msg
     */
    notify(sender, msg) {
        this.userList.forEach(user => {
            user.receiveMsg(sender, msg);
        });
    }
}
let group = new Group();
let jim = new User('jim', group);
let brook = new User('brook', group);
let lucy = new User('lucy', group);
jim.sendMsg('hello');
lucy.sendMsg('well done!');
//# sourceMappingURL=index.js.map