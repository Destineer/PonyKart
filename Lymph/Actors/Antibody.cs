﻿using Ponykart.Phys;
using Ponykart.Stuff;
using Mogre;
using Mogre.PhysX;

namespace Ponykart.Actors
{
	///<summary> Antibody projectile, shot by Lymphy. </summary>
	public class Antibody : Projectile
	{
		
		public long TimeCreated { get; set; }
		public bool HasBeenAttached { get; set; }

		protected override ShapeDesc ShapeDesc {
			get { return new SphereShapeDesc(0.1f); }
		}
		protected override uint DefaultCollisionGroupID {
			get { return Groups.CollidablePushableID; }
		}
		protected override string DefaultModel {
			get { return "antibody.mesh"; }
		}
		protected override float DefaultMoveSpeed {
			get { return 0.003f; }
		}
		protected override MoveBehaviour DefaultMoveBehaviour {
			get { return MoveBehaviour.IGNORE; }
		}
		protected override string DefaultMaterial {
			get { return null; }
		}

		/// <summary>
		/// Constructor for an antibody
		/// </summary>
		/// <param name="name">The name of the SceneNode. Should not have an ID on it.</param>
		/// <param name="colour">The colour of the ribbon</param>
		public Antibody(ThingTemplate tt)
			: base(tt)
		{
			
			//this.TimeCreated = DateTime.UtcNow.Ticks / 10000; //need to divide by 10,000 to get ms

			Launch.Log("Creating antibody #" + ID + " with name \"" + tt.StringTokens["Name"] + "\"");

			CreateRibbon(4, 20, ColourValue.Red, 0.2f);
			HasBeenAttached = false;
		}
	}
}