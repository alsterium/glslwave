#version 150 core
uniform float time;
uniform vec2 size;
out vec4 fragment;

vec3 lightDir = normalize(vec3(0.0, 0.0, 1.0));

mat3 rotmat_x(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	return mat3(1.0, 0.0, 0.0,
				0.0,   c,  -s,
				0.0,   s,   c); 

}

mat3 rotmat_y(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	return mat3(c  , 0.0,   s,
				0.0, 1.0, 0.0,
				-s , 0.0,   c);
}

vec3 trans(vec3 p)
{
	return mod(p,4.0) - 2.0;
}

// sphere
float sphere(vec3 p, float r)
{
	return length(trans(p)) - r;
}

//Box func
float udBox(vec3 p, vec3 b)
{
	return length(max(abs(trans(p)) - b, 0.0));
}

// sphere
float dist_func(vec3 pos, float size)
{
	return sphere(pos, size);

}

float dist_func(vec3 pos, vec3 size)
{
	return udBox(pos, size);
}

vec3 getNormal(vec3 pos, float size)
{

	float ep = 0.0001;
	return normalize(vec3(
		dist_func(pos, size) - dist_func(vec3(pos.x - ep, pos.y, pos.z), size),
		dist_func(pos, size) - dist_func(vec3(pos.x, pos.y - ep, pos.z), size),
		dist_func(pos, size) - dist_func(vec3(pos.x, pos.y, pos.z - ep), size)
		));

}

vec3 getNormal(vec3 pos, vec3 size)
{

	float ep = 0.0001;
	return normalize(vec3(
		dist_func(pos, size) - dist_func(vec3(pos.x - ep, pos.y, pos.z), size),
		dist_func(pos, size) - dist_func(vec3(pos.x, pos.y - ep, pos.z), size),
		dist_func(pos, size) - dist_func(vec3(pos.x, pos.y, pos.z - ep), size)
		));

}

void main()
{
    vec2 pos = (gl_FragCoord.xy * 2.0 -  size.xy) / min(size.x, size.y);
    
    vec3 col = vec3(0.);
    
    vec3 cameraPos = vec3(0., 0., -5.0);
    
    //define ray
    vec3 ray = normalize(vec3(pos,0.) - cameraPos);
    
    //init position of ray
    vec3 cur = cameraPos;
    
    //object size
    vec3 size = vec3(0.3);
    //float size = 1.0;
    
    //rotation matrix
    mat3 rot = rotmat_x(time) * rotmat_y(sin(time));
    
    
    for(int i = 0; i < 2000; i++){
    	float d = dist_func(rot * cur, size);
    	if(abs(d) < 0.0001)
    	{
    		//get Housen
    		vec3 normal = getNormal(cur, size);
    		float diff = clamp(dot(normal, lightDir),0.1,1.0);
    		col = vec3(diff) + vec3(1.0,113./255.,206./255.);
    		break;
    	}else{
    		col = vec3(5./255.,1.0,161./255.);
    	}
    	cur += ray * d;
    }
    
    //vec4 color = vec4(1.0-0.2,0.98-.2,0.58-.2,1.0);
    vec4 color = vec4(col,1.);
    fragment = color;
}
