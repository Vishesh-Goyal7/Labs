    let employees = [];
    let empID = 1;

    $(document).ready(function(){
    // Add Employee
    $("#employeeForm").submit(function(event){
        event.preventDefault(); // Prevent page refresh

        let name = $("#name").val();
        let age = $("#age").val();
        let department = $("#department").val();

        employees.push({ id: empID++, name: name, age: age, department: department });
        displayEmployees();
        $("#employeeForm")[0].reset(); // Clear form
    });

    // Display Employees
    function displayEmployees() {
        $("#employeeTable").html("");
        employees.forEach((emp, index) => {
            $("#employeeTable").append(`
                <tr>
                    <td>${emp.id}</td>
                    <td>${emp.name}</td>
                    <td>${emp.age}</td>
                    <td>${emp.department}</td>
                    <td>
                        <button class="btn btn-warning btn-sm editBtn" data-id="${index}">Edit</button>
                        <button class="btn btn-danger btn-sm deleteBtn" data-id="${index}">Delete</button>
                    </td>
                </tr>
            `);
        });
    }

    // Delete Employee
    $(document).on("click", ".deleteBtn", function(){
        let id = $(this).data("id");
        employees.splice(id, 1);
        displayEmployees();
    });

    // Edit Employee
    $(document).on("click", ".editBtn", function(){
        let id = $(this).data("id");
        let emp = employees[id];

        $("#name").val(emp.name);
        $("#age").val(emp.age);
        $("#department").val(emp.department);

        // Change button text to Update
        $("#employeeForm button").text("Update Employee").removeClass("btn-success").addClass("btn-primary");

        // On Update
        $("#employeeForm").off("submit").on("submit", function(event){
            event.preventDefault();
            employees[id].name = $("#name").val();
            employees[id].age = $("#age").val();
            employees[id].department = $("#department").val();
            displayEmployees();

            // Reset form and button
            $("#employeeForm")[0].reset();
            $("#employeeForm button").text("Add Employee").removeClass("btn-primary").addClass("btn-success");
            $("#employeeForm").off("submit").on("submit", function(event){
                event.preventDefault();
                let name = $("#name").val();
                let age = $("#age").val();
                let department = $("#department").val();
                employees.push({ id: empID++, name: name, age: age, department: department });
                displayEmployees();
                $("#employeeForm")[0].reset();
            });
        });
    });
});