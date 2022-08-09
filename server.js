const express = require('express');
const app = express();
const port = 3000;

app.use(express.static('generator'));
app.get('/', (req,res)=> {
	res.send("workout app");
})
app.listen(port, ()=> {
	console.log("server listening....");
})

