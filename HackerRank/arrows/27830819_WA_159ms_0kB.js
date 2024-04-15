var my_function = (arr) => {
	var res = [];
	for (let i = 0; i < arr.length; i++)
		if (i & 1) {
			res.push(arr[i]);
		}
	for (let i = arr.length - 1; i >= 0; i--)
		if (i & 1 ^ 1) {
			res.push(arr[i]);
		}
	return res;
};