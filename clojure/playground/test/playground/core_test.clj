(ns playground.core-test
  (:require [clojure.test :refer :all]
            [playground.core :refer :all]))


(deftest kth-test
  (testing "test kth"
    (is (= (playground.core/kth [1] 1) 1))
    (is (= (playground.core/kth [1, 2] 2) 2))
    (is (= (playground.core/kth [2, 1] 2) 2))
    (is (= (playground.core/kth [2, 1] 3) nil))
    (is (= (playground.core/kth [1] 0) nil))
    (is (= (playground.core/kth [1] -1) nil))
    ))

  