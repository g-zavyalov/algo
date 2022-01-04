for((i = 1; ; ++i)); do
  echo $i
  ./gen $i > generated_test
  # cat generated_test
  ./B < generated_test > stress_my
  ./solution < generated_test > stress_other
  diff -w stress_my stress_other || break
done
echo "ALL TESTS PASSED"
