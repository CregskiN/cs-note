
// 图形接口
interface Shape {
    isHidden: boolean;
    name: string;
    draw: () => void;
    remove: () => void;
}

// 两种图元
// 圆形
class Circle implements Shape {
    public isHidden: boolean;
    public name: string;

    constructor(name: string) {
        this.isHidden = false;
        this.name = name;
    }

    draw() {
        if (!this.isHidden) {
            this.isHidden = false;
            console.log(`draw circle: ${this.name}`);
        } else {
            console.warn(`${this.name} 已经存在了`);
        }
    }

    remove() {
        if (!this.isHidden) {
            this.isHidden = true;
            console.log(`remove circle: ${this.name}`);
        } else {
            console.warn(`${this.name} 不存在`);
        }
    }
}

// 矩形
class Rectangle implements Shape {
    public isHidden: boolean;
    public name: string;

    constructor(name: string) {
        this.isHidden = false;
        this.name = name;
    }

    draw() {
        if (!this.isHidden) {
            this.isHidden = false;
            console.log(`draw Rectangle: ${this.name}`);
        } else {
            console.warn(`${this.name} 已经存在了`);
        }
    }

    remove() {
        if (!this.isHidden) {
            this.isHidden = true;
            console.log(`remove Rectangle: ${this.name}`);
        } else {
            console.warn(`${this.name} 不存在`);
        }
    }
}

/**
 * 图元工厂
 * 属性：实例、图元池
 * 
 * 
 */
class GraphFactory {
    static readonly instance: GraphFactory = new GraphFactory();
    private graphPool: { [key: string]: Shape[] } = {}; // 以函数名为 key，数组元素为图元对象


    public getCircle(newName: string): Circle {
        return this.getShape(newName, Circle);
    }

    public getRectangle(newName: string): Rectangle {
        return this.getShape(newName, Rectangle);
    }

    public removeAll() { //删除所有
        console.log('remove all');
        for (let item in this.graphPool) {
            this.graphPool[item].forEach(o => o.isHidden = true);
        }
    }

    /**
     * 遍历图元池，获取某状态的图元数量
     * @param isHidden 
     */
    public getCount(isHidden: boolean): number {
        let count = 0;
        for (let key in this.graphPool) {
            // 遍历线程池的索引
            count = count + this.graphPool[key].filter(s => s.isHidden === isHidden).length;
        }
        return count;
    }

    // 获取图元
    private getShape(newName: string, shapeConstructor: typeof Circle | typeof Rectangle): Shape {
        if (this.graphPool[shapeConstructor.name]) {
            // 图元池 已有该图形，拿出来复用
            const shape = this.graphPool[shapeConstructor.name].find(s => s.isHidden); // find 返回第一个返回true的元素
            if (shape) {
                shape.isHidden = false;
                shape.name = newName;
                return shape;
            }
        }
        // 图元池 没有该图形，new 一个push进去
        const shape = new shapeConstructor(newName);
        this.graphPool[shapeConstructor.name] = this.graphPool[shapeConstructor.name] || [];
        this.graphPool[shapeConstructor.name].push(shape);
        return shape;
    }
}

const num = 5;
console.log('create elements');


for (let i = 1; i <= num; i++) {
    let circle = GraphFactory.instance.getCircle(`circle ${i}`);
    let rectangle = GraphFactory.instance.getRectangle(`rectangle ${i}`);
    console.group();
    console.log(circle);
    console.log(rectangle);
    circle.draw();
    rectangle.draw();
    console.groupEnd();

}
console.log(GraphFactory.instance);


console.log(`element count: ${GraphFactory.instance.getCount(false)}`);

GraphFactory.instance.removeAll();

console.log(`visible element count: ${GraphFactory.instance.getCount(false)}`);
console.log(`hidden element count: ${GraphFactory.instance.getCount(true)}`);

console.log('create elements again');

for (let i = 1; i <= num; i++) {
    let circle = GraphFactory.instance.getCircle(`new circle ${i}`);
    let rectangle = GraphFactory.instance.getRectangle(`new rectangle ${i}`);

    circle.draw();
    rectangle.draw();
}

console.log(`visible element count: ${GraphFactory.instance.getCount(false)}`);
console.log(`hidden element count: ${GraphFactory.instance.getCount(true)}`);