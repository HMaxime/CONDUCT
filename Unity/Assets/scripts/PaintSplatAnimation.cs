using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Threading;
using System.Threading.Tasks;
using DecalSystem;

public class PaintSplatAnimation : MonoBehaviour
{
    // Start is called before the first frame update
    public bool isOriginal = true;
    public int duration = 1000; //temps ou le splat de peinture reste affiché
    public float step = 0.5f; //rapidité du fade (entre 0.01 et 0.05)
    MeshRenderer rend;

    void Start()
    {
        //initialise le mesh
        var decal = this.GetComponent<Decal>();
        if (decal)
        {
            var filter = decal.GetComponent<MeshFilter>();
            var mesh = filter.mesh;
            if (mesh != null)
            {
                mesh.name = "DecalMesh";
                filter.mesh = mesh;
            }
            DecalBuilder.Build(decal);

        }
        rend  = GetComponent<MeshRenderer>();
        Color c = rend.material.color;
        c.a = 0f;
        rend.material.color = c;
        StartCoroutine("FadeIn");
        attente();
    }

    IEnumerator FadeIn()
    {
        for (float f = 0.00f; f <= 1; f += step){
            Color c = rend.material.color;
            c.a = f;
            rend.material.color = c;
            yield return new WaitForSeconds(0.05f);
        }

    }

    IEnumerator FadeOut()
    {
        for (float f = 1f; f >= 0.00f; f -= step){
            Color c = rend.material.color;
            c.a = f;
            rend.material.color = c;
            yield return new WaitForSeconds(0.05f);
        }
        if (!isOriginal){
            Object.Destroy(this.gameObject);
        }

    }

    public async Task attente()  
    {  
        await Task.Delay(duration);  
        StartCoroutine("FadeOut");
    }
}
