var prettyBits = function(array) {
	//instead of arrays, show strings
	return array.toString().split(',').join('');
}

var flip = function(array, index) {
	if (typeof (index) != 'undefined') {
		array[index] = +!array[index]; // "+" to cast bool to int
	}else{
		for (var i=0; i < array.length; i++){
			array[i] = +!array[i];
		}
	}
}

var getCombinationKey = function(fromBits){
	bitsKeyArray = [...fromBits]; // copy from "fromBits"
	bitsKey = prettyBits(bitsKeyArray);
	bitsKey = bitsKey.split('0').join(''); // remove all zeroes
	return bitsKey;
}

var getPreviousCombinations = function(n, combinations, fromBits, firstBits){
	var breakup = [];
	var breakups = [];
	var zeros = '';
	var bitsKey = getCombinationKey(fromBits);
	
	if (combinations[bitsKey]) {
		for (var i=0; i < combinations[bitsKey].length; i++) {
			breakup = [];
			breakup.push(prettyBits(firstBits));
			for(var j =0; j < combinations[bitsKey][i].length; j++) {
				zeros = '';
				for (var z=0; z < fromBits.length - combinations[bitsKey][i][j].length; z++){
					zeros += '0';
				}
				breakup.push(zeros + combinations[bitsKey][i][j]);
			}
			breakups.push(breakup);
		}
	}

	return breakups;
}

var findCombinations = function(n, combinations) {
	var bits = [];
	var breakup = [];
	var breakups = [];
	var index = n-1;
	var previousCombinations;

	for (var i=0; i < n; i++) {
		bits[i] = 1; // construct a full 1's bitset
	}


	while(index > 0) {
	    breakup = [];

	    flip(bits, index);
		breakup.push(prettyBits(bits));

		copyBits = [...bits];
		flip(copyBits);
		breakup.push(prettyBits(copyBits));

	    breakups.push(breakup);
	    previousCombinations = getPreviousCombinations(n, combinations, copyBits, bits)
		breakups = breakups.concat(previousCombinations);

	    index--;
	}

	return breakups;

}

var main = function(n) {
	var breakups = [];
	var combinations = {};
	var key = '11';
	var keyToPush = '1';

	for (var i=2; i <= n; i++) {
		combinations[key] = findCombinations(i, combinations);
		key += '1';
		keyToPush += '1';
	}
	combinations[keyToPush].unshift([keyToPush]); //unshift = push front
	console.log(combinations[keyToPush]);
}


main(5);