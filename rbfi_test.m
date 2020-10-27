% RBFI Test Code
shape = 0.25;
control_points = [5, -6, -2 ,4, -8; 1, 9, -7, 1, -3; 0, 0, -1, -6, -7; 1, 6, 1, 7, 0];
visual_points = [1, 0, -9, -6, 3; 0, 2, 5, 8, -8];

rbf = @(r, s) (exp(-(r*s)^2));

interpol = zeros(columns(control_points), columns(control_points));
for i = 1:columns(control_points)
  for j = i:columns(control_points)
    interpol(i,j) = rbf(norm(visual_points(:, i) - visual_points(:, j)), shape);
    if i != j
      interpol(j,i) = interpol(i,j);
    endif
  endfor
endfor

weights = zeros(columns(control_points), rows(control_points));
for i = 1:columns(weights)
  weights(:, i) = linsolve(interpol, transpose(control_points(i,:)));
endfor

p = [5; -7];
result = zeros(rows(control_points), 1);
for i = 1:rows(control_points)
  for j = 1:columns(control_points)
    result(i, 1) += weights(j, i) * rbf(norm(visual_points(:, j) - p), shape);
  endfor
endfor
result