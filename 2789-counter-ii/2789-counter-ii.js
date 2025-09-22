/**
 * @param {integer} init
 * @return { increment: Function, decrement: Function, reset: Function }
 */
var createCounter = function(init) {
    let P = init;
    
    function increment(){
        return P+=1;
    }

    function decrement(){
        return P-=1;
    }

    function reset(){
        return (P=init);
    }
    return {increment , decrement , reset};
};

/**
 * const counter = createCounter(5)
 * counter.increment(); // 6
 * counter.reset(); // 5
 * counter.decrement(); // 4
 */