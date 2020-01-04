(ns playground.core)

(defn one []
  1)

(defn kth [lst k]
  (let [idx (- k 1)]
    (if (<= 0 idx (- (count lst) 1))
      (nth (sort lst) idx)
      nil)))

