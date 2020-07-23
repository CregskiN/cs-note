class Man {
    job: string;
    constructor(readonly name: string) { }
    earnMoney() {
        console.log(`earning money`)
    }
}

interface HumanRule extends Man {
    nose: string;
    mouth: string;
    ear: string;
    eye: string;
    eyebrow: string
}

const e = document.getElementById('Bvideo');
console.log(e);