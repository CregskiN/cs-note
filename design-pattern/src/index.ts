
abstract class Observer {
    public name: string;

    constructor(name: string) {
        this.name = name;
    }

    abstract sendMsg(msg: string): void;
    abstract receiveMsg(sender: Observer, msg: string): void;
}

interface Subject {
    register(observer: Observer): void;
    unregister(observer: Observer): void;
    sendMsg(sender: Observer, msg: string): void;
}


// 用户类
class User extends Observer {
    private subject: Subject;

    constructor(name: string, subject: Subject) {
        super(name);
        this.subject = subject;
        this.subject.register(this);
    }

    public sendMsg(msg: string) {
        console.log(`${this.name} 发送了消息，${msg}`);
        this.subject.sendMsg(this, msg);
    }

    public receiveMsg(sender: Observer, msg: string) {
        console.log(`${this.name} 收到来自 ${sender.name} 的消息，${msg}`);
    }
}

// 群组
class Group implements Subject {
    private userList: Observer[];

    constructor() {
        this.userList = [];
    }

    register(observer: Observer) {
        this.userList.push(observer);
    }

    unregister(observer: Observer) {
        const index = this.userList.indexOf(observer);
        if (index > -1) {
            this.userList.splice(index, 1);
        }
    }

    sendMsg(sender: Observer, msg: string) {
        console.log(`群组收到${sender.name} 发来的消息，${msg} 通知所有人`);
        this.notify(sender, msg);
    }

    /**
     * 发布通知
     * @param sender 
     * @param msg 
     */
    private notify(sender: Observer, msg: string) {
        this.userList.forEach(user => {
            user.receiveMsg(sender, msg);
        })
    }
}

let group = new Group();
let jim = new User('jim', group);
let brook = new User('brook', group);
let lucy = new User('lucy', group);

jim.sendMsg('hello');
lucy.sendMsg('well done!');