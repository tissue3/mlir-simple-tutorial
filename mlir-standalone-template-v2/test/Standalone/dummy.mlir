// RUN: standalone-opt %s 

module {
    // CHECK-LABEL: func @bar()
    func @bar() {
        %0 = constant 5 : i32
        // CHECK: %{{.*}} = standalone.read_attr %{{.*}} : i32
        %res = standalone.foo %0 : i32
        return
    }
}
