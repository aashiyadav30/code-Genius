const express = require("express");
const app = express();
const router = express.Router();
const bodyP = require("body-parser");
const compiler = require("compilex");
const path = require('path');
const options = { stats: true };
compiler.init(options);

app.use(bodyP.json());
app.use(express.static(path.join(__dirname, 'public')));
app.use("/codemirror-5.65.18", express.static("C:/Users/ajeet/Downloads/CodeEditor1/codemirror/codemirror-5.65.18"));


// ✅ Route to serve the homepage
app.get("/", function (req, res) {
    compiler.flush(() => console.log("Deleted previous compilation files."));
    res.redirect("/homepage.html");

});

// ✅ Route to handle "Create Project" button click and redirect to index.html
app.get("/create-project", function (req, res) {
    res.redirect("/index.html"); // Redirect to index.html
});



// ✅ Compilation route for executing code
app.post("/compile", function (req, res) {
    const { code, input, lang } = req.body;
    let envData = { OS: "windows", options: { timeout: 10000 } };

    const formatErrorMessage = (error, code) => {
        if (!error) return "Unknown error occurred.";

        const match = error.match(/(line (\d+))/i);
        if (match && match[2]) {
            const errorLine = parseInt(match[2]);
            const codeLines = code.split("\n");

            let formattedCode = codeLines
                .map((line, index) =>
                    index + 1 === errorLine
                        ? `>> ${index + 1}: ${line}   <-- ERROR HERE`
                        : `   ${index + 1}: ${line}`
                )
                .join("\n");

            return `Compilation/Runtime Error:\n${error}\n\nHighlighted Code:\n${formattedCode}`;
        }

        return `Compilation/Runtime Error:\n${error}`;
    };

    const handleResponse = (data) => {
        if (data.output) {
            res.send({ output: data.output });
        } else if (data.error) {
            res.send({ output: formatErrorMessage(data.error, code) });
        } else {
            res.send({ output: "Unknown error occurred." });
        }
    };

    try {
        switch (lang) {
            case "Cpp":
                envData.cmd = "g++";
                input
                    ? compiler.compileCPPWithInput(envData, code, input, handleResponse)
                    : compiler.compileCPP(envData, code, handleResponse);
                break;

            case "Java":
                input
                    ? compiler.compileJavaWithInput(envData, code, input, handleResponse)
                    : compiler.compileJava(envData, code, handleResponse);
                break;

            case "Python":
                input
                    ? compiler.compilePythonWithInput(envData, code, input, handleResponse)
                    : compiler.compilePython(envData, code, handleResponse);
                break;

            default:
                res.send({ output: "Unsupported language selected." });
        }
    } catch (e) {
        console.error("Server-side error:", e);
        res.send({ output: "Internal server error occurred." });
    }
});

app.listen(8000, () => {
    console.log("Server running on http://localhost:8000/");
});
