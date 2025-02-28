$(document).ready(function(){
    let direction = 1; // 1 for right, -1 for left

    $("#moveBtn").click(function(){
        let moveDistance = 300; // Distance to move
        let container = $("#container");

        container.animate({ left: `+=${moveDistance * direction}px` }, 1000, function(){
            direction *= -1; // Reverse direction for circular motion
        });
    });
});
