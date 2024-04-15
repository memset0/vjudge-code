for (let forward of my_array) {
	let backward = "";
	for (let i = forward.length - 1; i >= 0; i--) {
		backward += forward[i];
	}
	if (forward == backward) {
		console.log(forward);
	}
}