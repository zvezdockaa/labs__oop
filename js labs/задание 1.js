let resultWord = function(str) {
    let minLength = str.length;
    let minWords = [];
    let word = '';
    let words = str.split(' ');
    minLength = words[0].length;
    let lenV = words.reduce((min, value) => {
        return (min > value.length) ? value.length :min;
    }, minLength);
    let totalStr = words.filter(function(word) {
        return word.length === lenV;
    });
    console.log(lenV);
    console.log(totalStr);

}
    resultWord("Hello world fi fi fi");



    // for (let i = 0; i < words.length; i++) {
    //  
    //         if (word.length > 0) {
    //             if (word.length < minLength) {
    //                 
    //                 minWords = [word];
    //             } 
    //             else if (word.length === minLength) {
    //                 minWords.push(word);
    //             }
    //             word = '';
    //         }
    //     }
    // }
    //return minWords.join(' ');
//};

// let string = "Hello world    fi        gi     as ";
// let result = resultWord(string);
// console.log(result);