"use strict";
function handleChange() {
    console.log('oninput事件触发。div：a我input了');
}
function handleKeyDown() {
    console.log('onkeydown触发。div：a我keydown了');
}
const elem = document.getElementById('text');
class User {
    constructor(mediator) {
        this.mediator = mediator;
        this.mediator.registerClient(this);
    }
    getTaxi() {
        this.taxi = this.mediator.getCar();
    }
    pay() {
        if (this.taxi) {
            this.mediator.pay(this.taxi);
            console.log('client pay');
        }
        else {
            throw new Error('taxi is not define');
        }
    }
}
class Taxi {
    constructor(mediator) {
        this.mediator = mediator;
        this.isWorking = false;
        this.mediator.registerCar(this);
    }
    startWork() {
        this.isWorking = true;
        this.mediator.updateCarStatus(this);
        console.log('the car start work');
    }
    finishWork() {
        this.isWorking = false;
        this.mediator.updateCarStatus(this);
        console.log('the car finish work');
    }
}
class DiDi {
    constructor() {
        this.clientList = [];
        this.carList = [];
    }
    registerClient(client) {
        this.clientList.push(client);
    }
    registerCar(car) {
        this.carList.push(car);
    }
    getCar() {
        let car = this.carList.find(car => !car.isWorking);
        if (car) {
            car.startWork();
            return car;
        }
        else {
            throw new Error('there is not a free car, now!');
        }
    }
    pay(car) {
        car.finishWork();
    }
    updateCarStatus(car) {
        console.log(`车子状态：${car.isWorking ? '工作' : '闲置'}`);
    }
}
let didi = new DiDi();
let taxi = new Taxi(didi);
let user = new User(didi);
user.getTaxi();
user.pay();
//# sourceMappingURL=index.js.map