{
    init: function(elevators, floors) {

        function Node(data, priority) {
            this.data = data;
            this.priority = priority;
        }

        Node.prototype.toString = function() {
            var string = '';
            string += this.data;
            string += ', ';
            string += this.priority;
            return string;
        };
        

        // takes an array of objects with {data, priority}
        function PriorityQueue(arr) {
            this.heap = [null];
            if (arr) 
                for (var i = 0; i < arr.length; i++)
                    this.push(arr[i].data, arr[i].priority);
        }

        PriorityQueue.prototype = {
            empty: function() {
                return (this.heap === null || this.heap.length === 1);
            },
            push: function(data, priority) {
                var node = new Node(data, priority);
                this.bubble(this.heap.push(node) - 1);      
            },
            
            pushNode: function(node) {
                this.bubble(this.heap.push(node) - 1);      
            },
            // removes and returns the data of highest priority
            pop: function() {
                var topNode = this.heap[1];
                this.heap[1] = this.heap.pop();
                this.sink(1); 
                return topNode;
            },
            
            // bubbles node i up the binary tree based on
            // priority until heap conditions are restored
            bubble: function(i) {
                while (i > 1) { 
                    var parentIndex = i >> 1; // <=> floor(i/2)
                    
                    // if equal, no bubble (maintains insertion order)
                    if (!this.isHigherPriority(i, parentIndex)) 
                        break;
                    
                    this.swap(i, parentIndex);
                    i = parentIndex;
                }   
            },
                
            // does the opposite of the bubble() function
            sink: function(i) {
                while (i * 2 < this.heap.length) {
                    // if equal, left bubbles (maintains insertion order)
                    var leftHigher = !this.isHigherPriority(i * 2 + 1, i * 2);
                    var childIndex = leftHigher? i * 2 : i * 2 + 1;
                    
                    // if equal, sink happens (maintains insertion order)
                    if (this.isHigherPriority(i,childIndex)) break;
                    
                    this.swap(i, childIndex);
                    i = childIndex;
                }   
            },
                
            // swaps the addresses of 2 nodes
            swap: function(i, j) {
                var temp = this.heap[i];
                this.heap[i] = this.heap[j];
                this.heap[j] = temp;
            },
                
            // returns true if node i is higher priority than j
            isHigherPriority: function(i, j) {
                return this.heap[i].priority < this.heap[j].priority;
            }
        }

        PriorityQueue.prototype.toString = function() {
            var string = '';
            for (var i in this.heap) {
                string += this.heap[i];
                string += ', ';
            }
            return string;
        };

        // Rebuilds priorityQueue given a new node (increment priority if it matches an existing node)
        function rebuildPriorityQueueWithNewData(priorityQueue, node) {
            console.log("rebuildPriorityQueueWithNewData(" + priorityQueue.heap.toString() + ", " + node + ")");
            console.log("rebuildPriorityQueueWithNewData: BEFORE:");
            console.dir(priorityQueue);

            // If priorityQueue is empty, just put the node on it
            if (priorityQueue.empty()) {
                priorityQueue.pushNode(node);
                return priorityQueue;
            }

            var nodes = [];
            while (!priorityQueue.empty()) {
                nodes.push(priorityQueue.pop());
                break;
            }
            for (var i in nodes) {
                if (nodes[i].data === node.data) {
                    ++nodes[i].priority;
                }

                priorityQueue.pushNode(nodes[i]);
            }

            return priorityQueue;
        }

        console.log("=================================================== BEGIN ===================================================");

        var floorsPriorityQueue = new PriorityQueue();
        console.log("floorsPriorityQueue to start: " + floorsPriorityQueue.heap.toString());
        for (var i in elevators) {

            var elevator = elevators[i];

            elevator.floorQueue = new PriorityQueue();

            // If you're bored, go pick some people up
            elevator.on("idle", function() {
                if (floorsPriorityQueue.empty()) {
                    console.warn("floorsPriorityQueue is EMPTY!!!");
                    return;
                }
                var priorityFloorNode = floorsPriorityQueue.pop();
                this.goToFloor(priorityFloorNode.data);
            });

            elevator.on("floor_button_pressed", function(floorNum) {
                this.floorQueue = rebuildPriorityQueueWithNewData(this.floorQueue, new Node(floorNum, 1));
                console.log("elevator.floor_button_pressed: " + this.floorQueue);
                console.log("elevator.floor_button_pressed: loadFactor " + this.loadFactor());
                if (this.loadFactor() > 0.5) {
                    console.log("elevator.floor_button_pressed: loadFactor " + this.loadFactor());
                    if (this.floorQueue.empty()) {
                        if (floorsPriorityQueue.empty()) {
                            this.goToFloor(0);
                        } else {
                            this.goToFloor(floorsPriorityQueue.pop().data);
                        }
                    } else {
                        this.goToFloor(this.floorQueue.pop().data); 
                    }
                }
            });
        }

        for (var j in floors) {
            var floor = floors[j];

            floor.on("up_button_pressed", function() {
                console.log(this.floorNum() + " floor up pressed - rebuilding floorsPriorityQueue");
                floorsPriorityQueue = rebuildPriorityQueueWithNewData(floorsPriorityQueue, new Node(this.floorNum(), 1));
                console.log(floorsPriorityQueue);
            });

            floor.on("down_button_pressed", function() {
                console.log(this.floorNum() + " floor down pressed - rebuilding floorsPriorityQueue");
                floorsPriorityQueue = rebuildPriorityQueueWithNewData(floorsPriorityQueue, new Node(this.floorNum(), 1));
                console.log(floorsPriorityQueue);
            });
        }
    },


    update: function(dt, elevators, floors) { ;;; }
}
