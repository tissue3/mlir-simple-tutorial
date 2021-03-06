// RUN: standalone-opt %s 

module {
    // CHECK-LABEL: func @bar()
    func @bar() {
        %0 = constant 1 : i32
        // CHECK: %{{.*}} = standalone.foo %{{.*}} : i32
        %res = "standalone.foo" (%0) : (i32)->(i32)
        %res2 = "standalone.read_attr"(){attr = 22:i32} : ()->i32
        return
    }
}
