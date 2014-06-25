maxenemies = 50;

math.randomseed( os.time() )

Rotate = function(pointx, pointy, rotationAngle)
	cosAngle = math.cos(rotationAngle);
	sinAngle = math.sin(rotationAngle);

	l_x = (pointx * cosAngle) - (pointy * sinAngle);
	l_y = (pointx * sinAngle) + (pointy * cosAngle);
	
	return l_x, l_y;
end

Move = function (posx, posy, speed, deltaTime, rotationAngle, totalMovement)
	totalMovement = totalMovement + (speed*deltaTime);
	l_posx = totalMovement;
	l_posy = math.sin(totalMovement/8)*40;
	
	l_posx, l_posy = Rotate(l_posx, l_posy, rotationAngle);
	l_posx = l_posx + posx;
	l_posy = l_posy + posy;
	
	return l_posx, l_posy, totalMovement;
end

SpawnEnemy = function()
--	if totalEnemies < maxenemies then
		--totalEnemies = totalEnemies + 1;
		x = math.random(0, 800);
		y = math.random(0, 800);
		--x = 0;
		--y = 5;
		width = math.random(5, 40);;
		height = width;
		rotation = math.random(0,360);
		CreateEnemy(x, y, width, height, rotation);
--	end
end

