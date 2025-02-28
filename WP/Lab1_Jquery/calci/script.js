$(document).ready(function(){
    $("#calculateBtn").click(function(){
        let num1 = parseFloat($("#num1").val());
        let num2 = parseFloat($("#num2").val());
        let operation = $("#operation").val();
        let result;

        if (isNaN(num1) || isNaN(num2)) {
            $("#result").text("Result: Please enter valid numbers");
            return;
        }

        switch(operation) {
            case "add":
                result = num1 + num2;
                break;
            case "subtract":
                result = num1 - num2;
                break;
            case "multiply":
                result = num1 * num2;
                break;
            case "divide":
                if (num2 === 0) {
                    $("#result").text("Result: Cannot divide by zero");
                    return;
                }
                result = num1 / num2;
                break;
            default:
                result = "Invalid Operation";
        }

        $("#result").text("Result: " + result);
    });
});
